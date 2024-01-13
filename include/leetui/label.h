#ifndef LEETUI_LABEL_H
#define LEETUI_LABEL_H

#include <string>

#include "frame.h"

namespace leetui {
class Label : public Frame {
 public:
  Label(const std::string& font, const std::string& text, Frame* parent);

  std::string font() const;
  std::string text() const;

  void set_font(const std::string& font);
  void set_text(const std::string& text);

 protected:
  std::string font_;
  std::string text_;
};
}  // namespace leetui

#endif  // LEETUI_LABEL_H
