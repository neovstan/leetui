#include "window.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

#include "controller.h"
#include "frame.h"
#include "painter.h"
#include "point.h"
#include "resource.h"

leetui::Window::Window(std::unique_ptr<Painter> painter, std::unique_ptr<Controller> controller)
    : painter_{std::move(painter)},
      controller_{std::move(controller)},
      hovered_frame_{},
      focus_frame_{} {
  frames_tree_[nullptr] = {};

  auto mouse_button_down_slot =
      std::bind(&Window::mouse_button_down, this, std::placeholders::_1, std::placeholders::_2);

  auto mouse_button_up_slot =
      std::bind(&Window::mouse_button_up, this, std::placeholders::_1, std::placeholders::_2);

  auto mouse_move_slot = std::bind(&Window::mouse_move, this, std::placeholders::_1);
  auto mouse_wheel_slot = std::bind(&Window::mouse_wheel, this, std::placeholders::_1);

  auto key_down_slot = std::bind(&Window::key_down, this, std::placeholders::_1);
  auto key_up_slot = std::bind(&Window::key_up, this, std::placeholders::_1);

  controller_->mouse_button_down.connect(mouse_button_down_slot);
  controller_->mouse_button_up.connect(mouse_button_up_slot);
  controller_->mouse_move.connect(mouse_move_slot);
  controller_->mouse_wheel.connect(mouse_wheel_slot);

  controller_->key_down.connect(key_down_slot);
  controller_->key_up.connect(key_up_slot);
}

leetui::Point leetui::Window::position() const {
  return position_;
}

leetui::Size leetui::Window::size() const {
  return size_;
}

void leetui::Window::move(const Point& p) {
  position_ = p;
}

void leetui::Window::resize(const Size& size) {
  size_ = size;
}

void leetui::Window::process() {
  std::queue<Frame*> q;

  std::unordered_map<Frame*, Point> cs;
  std::unordered_map<Frame*, Point> p1;
  std::unordered_map<Frame*, Point> p2;
  std::unordered_map<Frame*, int> min_alpha;
  std::unordered_map<Frame*, bool> active;

  q.push(nullptr);

  cs[nullptr] = position_;
  p1[nullptr] = position();
  p2[nullptr] = position() + Point{size().width(), size().height()};
  active[nullptr] = true;

  std::map<MouseAction, Frame*> frames_clicked;
  std::map<MouseAction, Frame*> frames_pressed;

  auto prev_hovered_frame = hovered_frame_;

  painter()->push_scissor(position_, position_ + Point{size_.width(), size_.height()});

  while (!q.empty()) {
    const auto frame = q.front();
    q.pop();

    if (frame && !frame->label() && !*frame) continue;

    for (const auto child : frames_tree_.at(frame)) {
      if (!child->label() && !*child) continue;
      if (cs[child]) continue;

      if (frame) {
        if (child->color() != nothing) {
          min_alpha[child] = std::min(min_alpha[frame], child->alpha());
        } else
          min_alpha[child] = min_alpha[frame];
      } else {
        min_alpha[child] = 255;
      }

      active[child] = !((frame && !frame->active()) || !active[frame] || !child->active());

      cs[child] = cs[frame] + child->position();

      p1[child].set_x(std::max(cs[child].x(), p1[frame].x()));
      p1[child].set_y(std::max(cs[child].y(), p1[frame].y()));

      p2[child].set_x(std::min(cs[child].x() + child->size().width(), p2[frame].x()));
      p2[child].set_y(std::min(cs[child].y() + child->size().height(), p2[frame].y()));

      painter()->push_scissor(p1[child], p2[child]);

      q.push(child);

      child->process.emit();

      if (!child->label()) {
        draw_frame(cs[child], min_alpha[child], child);
      } else {
        draw_label(cs[child], min_alpha[child], dynamic_cast<Label*>(child));
      }

      painter()->pop_scissor();

      if (!active[child]) continue;

      for (auto& click : clicks_) {
        if (click.point.is_between_points(p1[child], p2[child])) {
          frames_clicked[click] = child;
        }
      }

      for (auto& press : presses_) {
        if (press.point.is_between_points(p1[child], p2[child])) {
          frames_pressed[press] = child;
        }
      }

      if (mouse_pos_.is_between_points(p1[child], p2[child]) &&
          !mouse_button_state_[Controller::MouseButton::left]) {
        hovered_frame_ = child;
      }
    }
  }

  painter()->pop_scissor();

  auto prev_focus_frame = focus_frame_;

  if (!clicks_.empty() && frames_clicked.empty()) {
    focus_frame_ = nullptr;
  }

  clicks_ = {};
  presses_ = {};

  for (auto& p : frames_clicked) {
    auto click = p.first;
    auto frame = p.second;
    frame->clicked.emit(click.point - cs[frame], click.button);
    focus_frame_ = frame;
  }

  for (auto& p : frames_pressed) {
    auto press = p.first;
    auto frame = p.second;
    if (frame != focus_frame_) continue;
    frame->pressed.emit(press.point - cs[frame], press.button);
  }

  if (prev_focus_frame != focus_frame_) {
    if (prev_focus_frame) prev_focus_frame->out_of_focus.emit();
    if (focus_frame_) focus_frame_->came_in_focus.emit();
  }

  if (prev_hovered_frame != hovered_frame_) {
    if (prev_hovered_frame) prev_hovered_frame->out_of_hover.emit();
    if (hovered_frame_) hovered_frame_->came_in_hover.emit();
  }

  if (hovered_frame_) {
    hovered_frame_->hover.emit(mouse_pos_ - cs[hovered_frame_]);
  }
}

void leetui::Window::add_font(const std::string& name, const std::string& resource, double size) {
  auto native = painter()->add_font(Resources::instance().get(resource), size);
  fonts_[name] = {native, size};
}

/**
 * I decided to add image parsing functionality in leetui, since this must be done when working with
 * abosolutely any graphic driver. Thus, we provide a raw graphics buffer as input to painter. All
 * he has to do is create a texture out of it.
 */
void leetui::Window::add_image(const std::string& name, const std::string& resource) {
  auto rsc = Resources::instance().get(resource);
  int width{}, height{};
  auto buffer = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(rsc.data),
                                      static_cast<int>(rsc.size), &width, &height, NULL, 4);
  auto native = painter()->add_image(
      {reinterpret_cast<const char*>(buffer), static_cast<std::uint64_t>(width * height)}, width,
      height);

  stbi_image_free(buffer);

  images_[name] = {native};
}

void leetui::Window::add_movie(const std::string& name, const std::string& resource) {
  auto rsc = Resources::instance().get(resource);

  Movie movie{};
  int *delays{}, width{}, height{}, frame_count{};
  // We decode the GIF image. The buffer contains a stream of frames
  auto buffer = stbi_load_gif_from_memory(reinterpret_cast<const stbi_uc*>(rsc.data),
                                          static_cast<int>(rsc.size), &delays, &width, &height,
                                          &frame_count, NULL, 4);
  auto frame_size = width * height * 4ULL;
  // Create a texture for each frame of a GIF image
  for (int i = 0; i < frame_count; ++i) {
    auto texture = painter()->add_image(
        {reinterpret_cast<const char*>(&buffer[frame_size * i]), frame_size}, width, height);

    movie.add_frame({delays[i], Image{texture}});
  }

  stbi_image_free(buffer);
  movies_[name] = movie;
}

leetui::Font leetui::Window::get_font(const std::string& name) const {
  return fonts_.at(name);
}

leetui::Image leetui::Window::get_image(const std::string& name) const {
  return images_.at(name);
}

leetui::Movie leetui::Window::get_movie(const std::string& name) const {
  return movies_.at(name);
}

leetui::Controller* leetui::Window::controller() const {
  return controller_.get();
}

leetui::Painter* leetui::Window::painter() const {
  return painter_.get();
}

void leetui::Window::add_frame(Frame* parent, Frame* child) {
  frames_tree_[parent].push_back(child);
  frames_tree_[child] = {};
}

void leetui::Window::remove_frame(Frame* parent, Frame* child) {
  auto& adj = frames_tree_[parent];
  auto it = std::find(adj.begin(), adj.end(), child);
  if (it != adj.end()) {
    if (focus_frame_ == child) focus_frame_ = nullptr;
    if (hovered_frame_ == child) hovered_frame_ = nullptr;
    for (auto frame : frames_tree_[child]) {
      if (focus_frame_ == frame) focus_frame_ = nullptr;
      if (hovered_frame_ == frame) hovered_frame_ = nullptr;
      delete frame;
    }
    adj.erase(it);
  }
}

void leetui::Window::draw_frame(Point cs, int min_alpha, Frame* frame) const {
  painter()->draw_rectangle(
      cs, cs + Point{frame->size().width(), frame->size().height()},
      frame->transparent() ? Rgb{0, 0, 0, 0} : frame->color().rgb().set_a(min_alpha),
      frame->rounding());
  if (frame->texture() && min_alpha > 0) {
    painter()->draw_image(frame->texture(), cs,
                          cs + Point{frame->size().width(), frame->size().height()});
  }
}

void leetui::Window::draw_label(Point cs, int min_alpha, Label* label) const {
  const auto font = get_font(label->font());
  painter()->draw_text(label->text(), font.native(), font.size(), cs,
                       label->color().rgb().set_a(min_alpha));
  const auto size = painter()->calc_text_size(font.native(), font.size(), label->text());
  label->resize(size);
}

void leetui::Window::mouse_button_down(const Point& p, Controller::MouseButton button) {
  clicks_.push_back({p, button});
  mouse_button_state_[button] = true;
}

void leetui::Window::mouse_button_up(const Point& p, Controller::MouseButton button) {
  presses_.push_back({p, button});
  mouse_button_state_[button] = false;
}

void leetui::Window::mouse_move(const Point& p) {
  mouse_pos_ = p;
}

void leetui::Window::mouse_wheel(double delta) {
  if (!hovered_frame_) return;
  for (Frame* frame = hovered_frame_; frame != nullptr; frame = frame->parent()) {
    frame->wheel.emit(delta);
  }
}

void leetui::Window::key_down(const Key& key) {
  if (focus_frame_) focus_frame_->key_down.emit(key);
}

void leetui::Window::key_up(const Key& key) {
  if (focus_frame_) focus_frame_->key_up.emit(key);
}
