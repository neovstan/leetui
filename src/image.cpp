#include "image.h"

#include "stb_image.h"

leetui::Image::Image() : native_{} {
}

leetui::Image::Image(Painter::native_texture_t native) : native_{native} {
}

leetui::Painter::native_font_t leetui::Image::native() const {
  return native_;
}
