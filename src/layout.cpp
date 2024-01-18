#include "layout.h"

#include <algorithm>

#include "frame.h"

leetui::Layout::Layout() {
}

leetui::Layout::Layout(Type type, Frame* frame)
    : type_{type}, frame_{frame}, padding_{}, distance_{}, alignment_{} {
  frame_->set_layout(this);
}

leetui::Size leetui::Layout::padding() const {
  return padding_;
}

double leetui::Layout::distance() const {
  return distance_;
}

leetui::Layout::Alignment leetui::Layout::alignment() const {
  return alignment_;
}

void leetui::Layout::set_padding(Size padding) {
  padding_ = padding;
  rebuild();
}

void leetui::Layout::set_distance(double distance) {
  distance_ = distance;
  rebuild();
}

void leetui::Layout::set_alignment(Alignment alignment) {
  alignment_ = alignment;
  rebuild();
}

void leetui::Layout::add_separator(double size) {
  auto sep = new Frame{frame_};
  sep->resize(type_ == horizontal ? Size{size, 0} : Size{0, size});
  add_item(sep);
}

void leetui::Layout::add_item(Frame* item) {
  items_.push_back(item);
  rebuild();
}

void leetui::Layout::remove_item(Frame* item) {
  auto it = std::find(items_.begin(), items_.end(), item);
  if (it != items_.end()) {
    items_.erase(it);
  }
  rebuild();
}

void leetui::Layout::rebuild() {
  if (type_ == Type::vertical) {
    Size new_size;
    new_size.set_height(2 * padding_.height() - distance_);

    Point last_pos{padding_.width(), padding_.height()};
    for (auto item : items_) {
      item->move(last_pos);

      last_pos.y() += item->size().height() + distance_;

      new_size.set_width(std::max(new_size.width(), item->size().width()));
      new_size.height() += item->size().height() + distance_;
    }

    new_size.width() += 2 * padding_.width();

    for (auto item : items_) {
      auto pos = item->position();
      if (alignment_ == Alignment::down) {
        pos.x() = new_size.width() - item->size().width();
      } else if (alignment_ == Alignment::center) {
        pos.x() = (new_size.width() - item->size().width()) / 2;
      }
      item->move(pos);
    }

    frame_->resize(new_size);
  } else if (type_ == Type::horizontal) {
    Size new_size;
    new_size.set_width(2 * padding_.width() - distance_);

    Point last_pos{padding_.width(), padding_.height()};
    for (auto item : items_) {
      item->move(last_pos);
      last_pos.x() += item->size().width() + distance_;

      new_size.set_height(std::max(new_size.height(), item->size().height()));
      new_size.width() += item->size().width() + distance_;
    }

    new_size.height() += 2 * padding_.height();

    for (auto item : items_) {
      auto pos = item->position();
      if (alignment_ == Alignment::down) {
        pos.y() = new_size.height() - item->size().height();
      } else if (alignment_ == Alignment::center) {
        pos.y() = (new_size.height() - item->size().height()) / 2;
      }
      item->move(pos);
    }

    frame_->resize(new_size);
  }
}
