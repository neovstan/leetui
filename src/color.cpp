#include "color.h"

leetui::Color::Color(const Rgb& color) : color_{color} {
}

leetui::Color::Color(int r, int g, int b, int a) : color_{r, g, b, a} {
}

leetui::Rgb leetui::Color::rgb() const {
  return color_;
}

bool leetui::operator==(const Color& lhs, const Color& rhs) {
  return lhs.rgb() == rhs.rgb();
}

bool leetui::operator!=(const Color& lhs, const Color& rhs) {
  return !(lhs == rhs);
}
