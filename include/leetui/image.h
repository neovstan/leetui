#ifndef LEETUI_IMAGE_H
#define LEETUI_IMAGE_H

#include "painter.h"

namespace leetui {
class Image {
 public:
  Image();
  Image(Painter::native_texture_t native);

  Painter::native_texture_t native() const;

 private:
  Painter::native_texture_t native_;
};
}  // namespace leetui

#endif  // LEETUI_IMAGE_H
