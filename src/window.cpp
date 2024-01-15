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
      position_{},
      size_{},
      tree_{this} {
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
  tree_.process();
}

void leetui::Window::add_font(const std::string& name, const std::string& resource, double size) {
  auto native = painter()->add_font(Resources::instance().get(resource), size);
  fonts_[name] = {native, size};
}

void leetui::Window::add_image(const std::string& name, const std::string& resource) {
  auto rc = Resources::instance().get(resource);

  int width, height;

  auto buffer = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(rc.data), int(rc.size),
                                      &width, &height, NULL, 4);

  auto native = painter()->add_image(
      {reinterpret_cast<const char*>(buffer), std::uint64_t(width * height)}, width, height);

  stbi_image_free(buffer);

  images_[name] = {native};
}

void leetui::Window::add_movie(const std::string& name, const std::string& resource) {
  auto rc = Resources::instance().get(resource);

  Movie movie;
  int *delays, width, height, frame_count;

  // We decode the GIF image. The buffer contains a stream of frames
  auto buffer = stbi_load_gif_from_memory(reinterpret_cast<const stbi_uc*>(rc.data),
                                          static_cast<int>(rc.size), &delays, &width, &height,
                                          &frame_count, NULL, 4);

  std::uint64_t frame_size = width * height * 4ull;

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

void leetui::Window::add_frame(Frame* frame) {
  tree_.add(frame, frame->parent());
}

void leetui::Window::remove_frame(Frame* frame) {
  tree_.remove(frame);
}

void leetui::Window::draw_frame(const Point& abs_pos, double opacity, Frame* frame) const {
  if (opacity <= 0) return;

  auto min_pos = abs_pos;
  auto max_pos = abs_pos + frame->size();

  double alpha = frame->color().rgb().a();

  if (!frame->movie().is_empty() && !frame->movie().is_paused()) {
    frame->movie().move_to_next_frame();
    frame->set_texture(frame->movie().current_frame().image.native());
  }

  if (frame->texture()) {
    painter()->draw_image(frame->texture(), min_pos, max_pos, alpha * opacity, frame->rounding());
  } else {
    painter()->draw_rectangle(min_pos, max_pos, frame->color().rgb().set_a(alpha * opacity),
                              frame->rounding());
  }
}

void leetui::Window::draw_label(Point abs_pos, double opacity, Label* label) const {
  const auto font = get_font(label->font());
  const auto size = painter()->calc_text_size(font.native(), font.size(), label->text());

  if (label->size() != size) {
    if (label->parent()) abs_pos -= label->parent()->position();
    label->resize(size);
    if (label->parent()) abs_pos += label->parent()->position();
  }

  double alpha = label->color().rgb().a();
  alpha *= opacity;

  painter()->draw_text(label->text(), font.native(), font.size(), abs_pos,
                       label->color().rgb().set_a(alpha));
}

void leetui::Window::mouse_button_down(const Point& p, Controller::MouseButton button) {
  clicks_.push_back({p, button});
  mouse_.button_state[button] = true;
}

void leetui::Window::mouse_button_up(const Point& p, Controller::MouseButton button) {
  presses_.push_back({p, button});
  mouse_.button_state[button] = false;
}

void leetui::Window::mouse_move(const Point& p) {
  mouse_.pos = p;
}

void leetui::Window::mouse_wheel(double delta) {
  if (!tree_.hovered_frame()) return;
  for (Frame* frame = tree_.hovered_frame(); frame != nullptr; frame = frame->parent()) {
    frame->wheel.emit(delta);
  }
}

void leetui::Window::key_down(const Key& key) {
  if (tree_.focus_frame()) tree_.focus_frame()->key_down.emit(key);
}

void leetui::Window::key_up(const Key& key) {
  if (tree_.focus_frame()) tree_.focus_frame()->key_up.emit(key);
}
