#ifndef LEETUI_TREE_H
#define LEETUI_TREE_H

#include <unordered_map>
#include <vector>

#include "mouse_action.h"
#include "point.h"

namespace leetui {
class Frame;
class Window;

class Tree {
 public:
  explicit Tree(Window* window);

 public:
  void add(Frame* frame, Frame* parent);
  void remove(Frame* frame);

 public:
  void process();
  void handle_events(Frame* frame);

 public:
  Frame* focus_frame() const;
  Frame* hovered_frame() const;

 private:
  bool can_frame_be_drawn(Frame* frame) const;

 private:
  Frame* focus_frame_;
  Frame* hovered_frame_;

 private:
  struct Vertex {
    Point abs_pos;
    Point min_pos;
    Point max_pos;
    double opacity;
    bool active;
  };

 private:
  Frame* const root_;
  Window* window_;
  std::unordered_map<Frame*, std::vector<Frame*>> adjacent_list_;
  std::unordered_map<Frame*, Vertex> last_process_info_;
  std::map<MouseAction, Frame*> frames_clicked_;
  std::map<MouseAction, Frame*> frames_pressed_;
};
}  // namespace leetui

#endif  // LEETUI_TREE_H
