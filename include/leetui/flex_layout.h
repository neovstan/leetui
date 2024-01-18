#ifndef LEETUI_FLEX_LAYOUT_H
#define LEETUI_FLEX_LAYOUT_H

#include <vector>

#include "layout.h"
#include "size.h"

namespace leetui {
class Frame;
class FlexLayout : private Layout {
 public:
  enum class Direction { vertical, horizontal };
  enum class Alignment { begin, center, end, between };

 public:
  FlexLayout(Frame* frame);

 public:
  void add_item(Frame* frame) override;
  void remove_item(Frame* frame) override;

 public:
  void rebuild() override;

 public:
  Size padding() const;
  Size distance() const;
  Direction direction() const;
  bool wrap() const;
  Alignment vertical_alignment() const;
  Alignment horizontal_alignment() const;

 public:
  void set_padding(const Size& padding);
  void set_distance(const Size& distance);
  void set_direction(Direction direction);
  void set_wrap(bool value);
  void set_vertical_alignment(Alignment alignment);
  void set_horizontal_alignment(Alignment alignment);

 protected:
  Frame* frame_;

 protected:
  Size padding_;
  Size distance_;
  Direction direction_;
  bool wrap_;
  Alignment vertical_alignment_;
  Alignment horizontal_alignment_;

 protected:
  std::vector<Frame*> items_;
};
}  // namespace leetui

#endif  // LEETUI_FLEX_LAYOUT_H
