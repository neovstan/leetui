#include "frame.h"

#include "cond_behavior.h"
#include "layout.h"
#include "window.h"

leetui::Frame::Frame(Window* window)
    : window_{window},
      parent_{},
      position_{},
      size_{},
      color_{nothing},
      opacity_{1.0},
      visible_{true},
      active_{true},
      rounding_{},
      layout_{},
      label_{},
      texture_{},
      popup_{} {
  window_->add_frame(this);
}

leetui::Frame::Frame(Frame* parent)
    : window_{parent->window()},
      parent_{parent},
      position_{},
      size_{},
      color_{nothing},
      opacity_{1.0},
      visible_{true},
      active_{true},
      rounding_{},
      layout_{},
      label_{},
      texture_{},
      popup_{} {
  window_->add_frame(this);
}

leetui::Frame::~Frame() {
  window_->remove_frame(this);
  if (layout_) delete layout_;
  if (parent() && parent()->layout()) parent()->layout()->remove_item(this);
  auto cb = cond_behaviors_;
  for (auto p : cb) delete p;
}

leetui::Window* leetui::Frame::window() const {
  return window_;
}

leetui::Frame* leetui::Frame::parent() const {
  return parent_;
}

leetui::Point leetui::Frame::position() const {
  return position_;
}

leetui::Size leetui::Frame::size() const {
  return size_;
}

leetui::Color leetui::Frame::color() const {
  return color_;
}

bool leetui::Frame::visible() const {
  return visible_;
}

bool leetui::Frame::active() const {
  return active_;
}

leetui::Corner leetui::Frame::rounding() const {
  return rounding_;
}

leetui::Layout* leetui::Frame::layout() const {
  return layout_;
}

bool leetui::Frame::label() const {
  return label_;
}

leetui::Painter::native_texture_t leetui::Frame::texture() const {
  return texture_;
}

double leetui::Frame::param(const std::string& key) {
  return params_[key];
}

double leetui::Frame::opacity() const {
  return opacity_;
}

bool leetui::Frame::popup() const {
  return popup_;
}

leetui::Movie& leetui::Frame::movie() {
  return movie_;
}

leetui::Frame::operator bool() const {
  return visible() && position() && size();
}

void leetui::Frame::move(const Point& position) {
  position_ = position;
}

void leetui::Frame::resize(const Size& size) {
  size_ = size;
  for (auto p = parent(); p != nullptr; p = p->parent()) {
    if (!p->layout()) break;
    p->layout()->rebuild();
  }
}

void leetui::Frame::set_color(const Color& color) {
  color_ = color;
}

void leetui::Frame::set_opacity(double opacity) {
  opacity_ = opacity;
}

void leetui::Frame::show() {
  visible_ = true;
}

void leetui::Frame::hide() {
  visible_ = false;
}

leetui::Frame* leetui::Frame::deepen(int depth) {
  auto frame = this;
  while (depth--) {
    frame = new Frame{frame};
    frame->move({0, 0});
    frame->resize({0, 0});
    frame->set_active(true);
    frame->set_popup(popup());
  }
  frame->set_active(active());
  return frame;
}

void leetui::Frame::set_active(bool active) {
  active_ = active;
}

void leetui::Frame::set_rounding(const Corner& rounding) {
  rounding_ = rounding;
}

void leetui::Frame::set_layout(Layout* layout) {
  layout_ = layout;
}

void leetui::Frame::set_texture(Painter::native_texture_t texture) {
  texture_ = texture;
}

void leetui::Frame::set_image(const std::string& image) {
  if (color_.rgb().a() == 0) color_ = color_.rgb().set_a(255);
  texture_ = window()->get_image(image).native();
}

void leetui::Frame::set_movie(const std::string& movie) {
  if (movie.empty()) {
    movie_ = {};
    return;
  }

  if (color_.rgb().a() == 0) color_ = color_.rgb().set_a(255);
  movie_ = window()->get_movie(movie);
}

void leetui::Frame::set_param(const std::string& key, double value) {
  params_[key] = value;
}

void leetui::Frame::set_popup(bool popup) {
  popup_ = popup;
}
