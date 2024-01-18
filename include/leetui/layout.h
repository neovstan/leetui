#ifndef LEETUI_LAYOUT_H
#define LEETUI_LAYOUT_H

#include <vector>

#include "size.h"

namespace leetui {
class Frame;

class Layout {
 public:
  enum Type { horizontal, vertical };
  enum class Alignment { up, down, center };

 public:
  Layout();
  Layout(Type type, Frame* frame);

 public:
  Size padding() const;
  double distance() const;
  Alignment alignment() const;

 public:
  void set_padding(Size padding);
  void set_distance(double distance);
  void set_alignment(Alignment alignment);

 public:
  void add_separator(double size);
  virtual void add_item(Frame* item);
  virtual void remove_item(Frame* item);

 public:
  virtual void rebuild();

 private:
  Type type_;
  Frame* frame_;
  std::vector<Frame*> items_;
  Size padding_;
  double distance_;
  Alignment alignment_;
};
}  // namespace leetui

#endif  // LEETUI_LAYOUT_H
