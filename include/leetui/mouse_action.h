#ifndef LEETUI_MOUSE_ACTION_H
#define LEETUI_MOUSE_ACTION_H

#include "point.h"
#include "controller.h"

namespace leetui {
struct MouseAction {
  Point point;
  Controller::MouseButton button;

  bool operator>(const MouseAction& rhs) const {
    using mb = leetui::Controller::MouseButton;
    auto a = point.x() + point.y();
    auto b = rhs.point.x() + rhs.point.y();

    if (a > b)
      return true;
    else if (a < b)
      return false;
    else
      return button == mb::left && rhs.button == mb::right;
  }
  bool operator<(const MouseAction& a) const {
    return a > *this;
  }
};
}  // namespace leetui

bool operator==(const leetui::MouseAction& lhs, const leetui::MouseAction& rhs);
bool operator!=(const leetui::MouseAction& lhs, const leetui::MouseAction& rhs);

#endif  // LEETUI_MOUSE_ACTION_H
