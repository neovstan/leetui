#include "movie.h"

leetui::Movie::Movie() : paused_{}, repeat_{true}, frame_counter_{} {
}

void leetui::Movie::pause() {
  paused_ = true;
}

void leetui::Movie::resume() {
  paused_ = false;
}

bool leetui::Movie::is_empty() const {
  return frames_.empty();
}

bool leetui::Movie::is_paused() const {
  return paused_;
}

leetui::native_movie_t leetui::Movie::current_frame() const {
  return frames_.at(frame_counter_);
}

void leetui::Movie::move_to_next_frame() {
  auto now = std::chrono::steady_clock::now();
  if (now - frame_timer_ < std::chrono::milliseconds{frames_[frame_counter_].delay}) return;

  if (frame_counter_ < frames_.size() - 1)
    ++frame_counter_;
  else if (repeat_)
    frame_counter_ = 0;

  frame_timer_ = now;
}

void leetui::Movie::add_frame(native_movie_t value) {
  frames_.push_back(value);
}

void leetui::Movie::set_repeat(bool value) {
  repeat_ = value;
}
