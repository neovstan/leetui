#include "viewport.h"

leetui::Viewport::Viewport(Frame* parent)
    : Frame{parent}, container_{new Frame{this}}, offset_{}, active_{true} {
  container_->move({0, 0});
  container_->resize({0, 0});
  container_->set_active(false);

  process.connect([this]() {
    offset_ = std::max(0.0, std::min(offset_, max_offset()));
    container()->move({container()->position().x(), -offset_});
  });

  wheel.connect([this](double delta) {
    if (!active_) return;

    static auto sign = [](double x) { return x / std::abs(x); };

    delta = -sign(delta) * 20;
    if (offset_ + delta < max_offset()) {
      offset_ += delta;
    }
  });
}

leetui::Frame* leetui::Viewport::container() const {
  return container_;
}

bool leetui::Viewport::active() const {
  return active_;
}

void leetui::Viewport::set_active(bool status) {
  active_ = status;
  container()->set_active(status);
}

double leetui::Viewport::max_offset() const {
  return container()->size().height() - size().height();
}
