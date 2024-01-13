#include "mouse_action.h"

bool operator==(const leetui::MouseAction& lhs, const leetui::MouseAction& rhs) {
  return lhs.point == rhs.point && lhs.button == rhs.button;
}

bool operator!=(const leetui::MouseAction& lhs, const leetui::MouseAction& rhs) {
  return !(lhs == rhs);
}
