#include "label.h"

leetui::Label::Label(const std::string& font, const std::string& text, Frame* parent)
    : Frame{parent}, font_{font}, text_{text} {
  label_ = true;
  color_ = white;
}

std::string leetui::Label::font() const {
  return font_;
}

std::string leetui::Label::text() const {
  return text_;
}

void leetui::Label::set_font(const std::string& font) {
  font_ = font;
}

void leetui::Label::set_text(const std::string& text) {
  text_ = text;
}
