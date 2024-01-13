#ifndef LEETUI_CONTROLLER_H
#define LEETUI_CONTROLLER_H

#include "keyboard.h"
#include "point.h"
#include "signal.h"

namespace leetui {
class Controller {
 public:
  enum class MouseButton { left, right, middle };

 public:
  explicit Controller(const Keyboard& keyboard);

  Keyboard keyboard() const;

 public:
  Signal<void(const Point&, MouseButton)> mouse_button_down;
  Signal<void(const Point&, MouseButton)> mouse_button_up;
  Signal<void(const Point&)> mouse_move;
  Signal<void(double)> mouse_wheel;
  Signal<void(const Key&)> key_down;
  Signal<void(const Key&)> key_up;

 private:
  Keyboard keyboard_;
};
}  // namespace leetui

#endif  // LEETUI_CONTROLLER_H
