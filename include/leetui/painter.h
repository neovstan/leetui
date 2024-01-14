#ifndef LEETUI_PAINTER_H
#define LEETUI_PAINTER_H

#include <string>

namespace leetui {
class Point;
class Vector;
class Color;
class Size;
struct Resource;

class Painter {
 public:
  using native_font_t = void*;
  using native_texture_t = void*;

 public:
  virtual void draw_rectangle(const Point& p1, const Point& p2, const Color& color,
                              double rounding = 0.0) = 0;
  virtual void push_scissor(const Point& p1, const Point& p2) = 0;
  virtual void pop_scissor() = 0;

  virtual native_font_t add_font(const Resource& resource, double size) = 0;
  virtual void draw_text(const std::string& text, native_font_t p, double size, const Point& pos,
                         const Color& color) = 0;
  virtual Size calc_text_size(native_font_t font, double size, const std::string& text) = 0;

  virtual native_texture_t add_image(const Resource& resource, std::uint32_t width,
                                     std::uint32_t height) = 0;
  virtual void draw_image(native_texture_t p, const Point& p1, const Point& p2) = 0;
};
}  // namespace leetui

#endif  // LEETUI_PAINTER_H
