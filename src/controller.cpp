#include "controller.h"

leetui::Controller::Controller(const Keyboard& keyboard) : keyboard_{keyboard} {
}

leetui::Keyboard leetui::Controller::keyboard() const {
  return keyboard_;
}
