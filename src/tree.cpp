#include "tree.h"

#include <algorithm>
#include <queue>

#include "frame.h"
#include "window.h"

leetui::Tree::Tree(Window* window)
    : root_{nullptr}, window_{window}, focus_frame_{}, hovered_frame_{} {
  adjacent_list_[root_] = {};
}

void leetui::Tree::add(Frame* frame, Frame* parent) {
  adjacent_list_[parent].push_back(frame);
  adjacent_list_[frame] = {};
}

void leetui::Tree::remove(Frame* frame) {
  Frame* parent = frame->parent();

  auto& adj = adjacent_list_[parent];
  auto it = std::find(adj.begin(), adj.end(), frame);
  if (it == adj.end()) return;

  if (focus_frame_ == frame) focus_frame_ = nullptr;
  if (hovered_frame_ == frame) hovered_frame_ = nullptr;

  for (Frame* child : adjacent_list_[frame]) {
    if (focus_frame_ == child) focus_frame_ = nullptr;
    if (hovered_frame_ == child) hovered_frame_ = nullptr;

    delete child;
  }

  adj.erase(it);
}

void leetui::Tree::process() {
  frames_clicked_ = {};
  frames_pressed_ = {};

  std::queue<Frame*> q;

  q.push(root_);

  auto& t = last_process_info_;
  auto prev_hovered_frame = hovered_frame_;

  t[root_] = {window_->position(), window_->position(), window_->position() + window_->size(), 1.0,
              true};

  window_->painter()->push_scissor(t[root_].min_pos, t[root_].max_pos);

  while (!q.empty()) {
    Frame* parent = q.front();
    q.pop();

    if (!can_frame_be_drawn(parent)) continue;

    for (Frame* child : adjacent_list_[parent]) {
      if (!can_frame_be_drawn(child)) continue;

      if (parent == root_) {
        t[child].opacity = child->opacity();
        t[child].active = child->active();
      } else {
        t[child].opacity = t[parent].opacity * child->opacity();
        t[child].active = parent->active() && t[parent].active && child->active();
      }

      auto& abs_pos = t[child].abs_pos;
      auto& min_pos = t[child].min_pos;
      auto& max_pos = t[child].max_pos;

      abs_pos = t[parent].abs_pos + child->position();

      if (!child->popup()) {
        min_pos.set_x(std::max(abs_pos.x(), t[parent].min_pos.x()));
        min_pos.set_y(std::max(abs_pos.y(), t[parent].min_pos.y()));

        max_pos.set_x(std::min(abs_pos.x() + child->size().width(), t[parent].max_pos.x()));
        max_pos.set_y(std::min(abs_pos.y() + child->size().height(), t[parent].max_pos.y()));

        window_->painter()->push_scissor(min_pos, max_pos);
      } else {
        min_pos = abs_pos;
        max_pos = abs_pos + child->size();
      }

      q.push(child);
      child->process.emit();

      if (!child->label()) {
        window_->draw_frame(abs_pos, t[child].opacity, child);
      } else {
        window_->draw_label(abs_pos, t[child].opacity, dynamic_cast<Label*>(child));
      }

      if (!child->popup()) window_->painter()->pop_scissor();
      if (t[child].active) handle_events(child);
    }
  }

  window_->painter()->pop_scissor();

  auto prev_focus_frame = focus_frame_;

  if (!window_->clicks_.empty() && frames_clicked_.empty()) {
    focus_frame_ = nullptr;
  }

  for (auto& p : frames_clicked_) {
    auto click = p.first;
    auto frame = p.second;
    frame->clicked.emit(click.point - t[frame].abs_pos, click.button);
    focus_frame_ = frame;
  }

  for (auto& p : frames_pressed_) {
    auto press = p.first;
    auto frame = p.second;
    if (frame != focus_frame_) continue;
    frame->pressed.emit(press.point - t[frame].abs_pos, press.button);
  }

  if (prev_focus_frame != focus_frame_) {
    if (prev_focus_frame) prev_focus_frame->out_of_focus.emit();
    if (focus_frame_) focus_frame_->came_in_focus.emit();
  }

  if (prev_hovered_frame != hovered_frame_) {
    if (prev_hovered_frame) prev_hovered_frame->out_of_hover.emit();
    if (hovered_frame_) hovered_frame_->came_in_hover.emit();
  }

  if (hovered_frame_) {
    hovered_frame_->hover.emit(window_->mouse_.pos - t[hovered_frame_].abs_pos);
  }

  window_->clicks_ = {};
  window_->presses_ = {};
}

void leetui::Tree::handle_events(Frame* frame) {
  auto& t = last_process_info_;
  auto& min_pos = t[frame].min_pos;
  auto& max_pos = t[frame].max_pos;

  for (auto& click : window_->clicks_) {
    if (!click.point.is_between_points(min_pos, max_pos)) continue;
    frames_clicked_[click] = frame;
  }

  for (auto& press : window_->presses_) {
    if (!press.point.is_between_points(min_pos, max_pos)) continue;
    frames_pressed_[press] = frame;
  }

  if (window_->mouse_.pos.is_between_points(min_pos, max_pos) &&
      !window_->mouse_.button_state[Controller::MouseButton::left]) {
    hovered_frame_ = frame;
  }
}

leetui::Frame* leetui::Tree::focus_frame() const {
  return focus_frame_;
}

leetui::Frame* leetui::Tree::hovered_frame() const {
  return hovered_frame_;
}

bool leetui::Tree::can_frame_be_drawn(Frame* frame) const {
  return !(frame && !frame->label() && !*frame);
}
