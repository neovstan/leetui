#ifndef LEETUI_FONT_H
#define LEETUI_FONT_H

#include "painter.h"

namespace leetui {
class Font {
 public:
  Font();
  Font(Painter::native_font_t native, double size);

  Painter::native_font_t native() const;
  double size() const;

 private:
  Painter::native_font_t native_;
  double size_;
};
}  // namespace leetui

#endif  // LEETUI_FONT_H
