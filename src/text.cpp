#include "text.h"

#include "label.h"
#include "layout.h"

leetui::Text::Text(const std::string& font, const std::string& text, Frame* parent)
    : Frame{parent},
      label_frame_{new Frame{this}},
      label_{new Label{font, text, label_frame_}},
      sep_{new Frame{this}},
      layout_{new Layout{Layout::vertical, this}},
      label_layout_{new leetui::Layout{leetui::Layout::horizontal, label_frame_}} {
  label_frame_->set_active(false);
  label_layout_->add_item(label_);
  layout_->add_item(label_frame_);
  layout_->add_item(sep_);
}

std::string leetui::Text::text() const {
  return label_->text();
}

leetui::Color leetui::Text::color() const {
  return label_->color();
}

leetui::Color leetui::Text::background_color() const {
  return label_frame_->color();
}

double leetui::Text::rounding() const {
  return label_frame_->rounding();
}

void leetui::Text::set_fixed_width(double width) {
  sep_->resize({width, 0});
}

void leetui::Text::set_alignment(Alignment alignment) {
  switch (alignment) {
    case Alignment::left:
      layout_->set_alignment(Layout::Alignment::up);
      break;
    case Alignment::right:
      layout_->set_alignment(Layout::Alignment::down);
      break;
    case Alignment::center:
      layout_->set_alignment(Layout::Alignment::center);
      break;
  }
}

void leetui::Text::set_text(const std::string& text) {
  label_->set_text(text);
}

void leetui::Text::set_padding(const Size& padding) {
  label_layout_->set_padding(padding);
}

void leetui::Text::set_color(const Color& color) {
  label_->set_color(color);
}

void leetui::Text::set_background_color(const Color& color) {
  label_frame_->set_color(color);
}

void leetui::Text::set_rounding(double x) {
  label_frame_->set_rounding(x);
}
