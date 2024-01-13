#ifndef LEETUI_COLOR_H
#define LEETUI_COLOR_H

#include "rgb.h"

namespace leetui {
class Color {
 public:
  Color(const Rgb& color);
  Color(int r, int g, int b, int a = 255);

  Rgb rgb() const;

 private:
  Rgb color_;
};

bool operator==(const Color& lhs, const Color& rhs);
bool operator!=(const Color& lhs, const Color& rhs);

const Color nothing{-1, -1, -1, -1};
const Color white{255, 255, 255};
const Color black{0, 0, 0};
const Color red{255, 0, 0};
const Color green{0, 255, 0};
const Color blue{0, 0, 255};
}  // namespace leetui

#endif  // LEETUI_COLOR_H
