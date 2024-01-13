#ifndef LEETUI_VIEWPORT_H
#define LEETUI_VIEWPORT_H

#include "frame.h"

namespace leetui {
class Viewport : public Frame {
 public:
  explicit Viewport(Frame* parent);

 public:
  Frame* container() const;
  bool active() const;

 public:
  void set_active(bool status);

 private:
  double max_offset() const;

 private:
  Frame* container_;
  double offset_;
  bool active_;
};
}  // namespace leetui

#endif  // LEETUI_VIEWPORT_H
