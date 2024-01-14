#include "movie.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

leetui::Movie::Movie() : repeat_{true}, frame_counter_{} {
}

// leetui::Movie::Movie(const Resource& resource, Frame* parent) {
//   int *delays{nullptr}, width{}, height{}, frames{};
//   auto buffer = stbi_load_gif_from_memory(reinterpret_cast<const stbi_uc*>(resource.data),
//                                           static_cast<int>(resource.size), &delays, &width,
//                                           &height, &frames, NULL, 4);
// }

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
