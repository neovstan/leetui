#ifndef LEETUI_MOVIE_H
#define LEETUI_MOVIE_H

#include <chrono>
#include <vector>

#include "image.h"

namespace leetui {
struct native_movie_t {
  int delay;
  Image image;
};

class Movie {
 public:
  Movie();

 public:
  void pause();
  void resume();

 public:
  bool is_empty() const;
  bool is_paused() const;

 public:
  native_movie_t current_frame() const;
  void move_to_next_frame();

 public:
  void add_frame(native_movie_t value);
  void set_repeat(bool value);

 private:
  bool paused_;
  bool repeat_;
  std::size_t frame_counter_;
  std::chrono::steady_clock::time_point frame_timer_;
  std::vector<native_movie_t> frames_;
};
}  // namespace leetui

#endif  // LEETUI_MOVIE_H
