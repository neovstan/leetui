#ifndef LEETUI_TEXT_H
#define LEETUI_TEXT_H

#include "frame.h"

namespace leetui {
class Label;
class Layout;

class Text : public Frame {
 public:
  enum class Alignment { left, right, center };

 public:
  Text(const std::string& font, const std::string& text, Frame* parent);

 public:
  std::string text() const;
  Color color() const;
  Color background_color() const;
  Corner rounding() const;

 public:
  void set_fixed_width(double width);
  void set_alignment(Alignment alignment);
  void set_text(const std::string& text);
  void set_padding(const Size& padding);
  void set_color(const Color& color);
  void set_background_color(const Color& color);
  void set_rounding(const Corner& x);

 private:
  Frame* label_frame_;
  Label* label_;
  Frame* sep_;
  Layout* layout_;
  Layout* label_layout_;
};
}  // namespace leetui

#endif  // LEETUI_TEXT_H
