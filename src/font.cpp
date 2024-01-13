#include "font.h"

leetui::Font::Font() : native_{}, size_{} {
}

leetui::Font::Font(Painter::native_font_t native, double size) : native_{native}, size_{size} {
}

leetui::Painter::native_font_t leetui::Font::native() const {
  return native_;
}

double leetui::Font::size() const {
  return size_;
}
