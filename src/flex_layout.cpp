#include "flex_layout.h"

#include <algorithm>

#include "frame.h"

leetui::FlexLayout::FlexLayout(Frame* frame)
    : frame_{frame},
      padding_{},
      distance_{},
      direction_{},
      wrap_{},
      vertical_alignment_{},
      horizontal_alignment_{},
      items_{} {
  frame_->set_layout(this);
}

void leetui::FlexLayout::add_item(Frame* frame) {
  items_.push_back(frame);
  rebuild();
}

void leetui::FlexLayout::remove_item(Frame* frame) {
  auto it = std::find(items_.begin(), items_.end(), frame);
  if (it != items_.end()) {
    items_.erase(it);
  }
  rebuild();
}

void leetui::FlexLayout::rebuild() {
  Size size{frame_->size() - padding_ - padding_};
  Size distance{distance_};

  struct build_information {
    Size max_size{0, 0};
    Point min_pos{0, 0};
    Point max_pos{0, 0};

    std::size_t max_count_in_h_line = 0;
    std::size_t max_count_in_v_line = 0;

    struct line {
      Size size;
      std::vector<Frame*> frames;
    };

    std::vector<line> lines;
  };

  auto update = [this](const Size& size, const Size& distance, build_information& out) {
    Point last_pos{out.min_pos};

    build_information::line current_line{};

    for (Frame* frame : items_) {
      Size element_size = frame->size();

      out.max_size.width() = std::max(out.max_size.width(), element_size.width());
      out.max_size.height() = std::max(out.max_size.height(), element_size.height());

      frame->move(padding_ + last_pos);

      switch (direction_) {
        case Direction::horizontal: {
          if (wrap_ && last_pos.x() + element_size.width() > size.width()) {
            last_pos.y() += current_line.size.height();
            last_pos.y() += distance.height();
            last_pos.x() = 0;

            frame->move(padding_ + last_pos);

            out.max_size.height() = element_size.height();

            out.lines.push_back(current_line);
            current_line = {};
          }

          current_line.frames.push_back(frame);

          Size end_pos{last_pos.x() + element_size.width(), last_pos.y() + element_size.height()};

          current_line.size.width() = end_pos.width();
          current_line.size.height() = std::max(current_line.size.height(), element_size.height());

          out.max_pos.x() = std::max(out.max_pos.x(), end_pos.width());
          out.max_pos.y() = std::max(out.max_pos.y(), end_pos.height());

          last_pos.x() += element_size.width();
          last_pos.x() += distance.width();

          out.max_count_in_h_line = std::max(out.max_count_in_h_line, current_line.frames.size());

          break;
        }

        case Direction::vertical: {
          if (wrap_ && last_pos.y() + element_size.height() > size.height()) {
            if (horizontal_alignment_ == Alignment::end) {
              last_pos.x() -= current_line.size.width();
              last_pos.x() -= distance.width();
            } else {
              last_pos.x() += current_line.size.width();
              last_pos.x() += distance.width();
            }

            last_pos.y() = 0;

            frame->move(padding_ + last_pos);

            out.max_size.width() = element_size.width();

            out.lines.push_back(current_line);
            current_line = {};
          }

          current_line.frames.push_back(frame);

          Size end_pos{last_pos.x() + element_size.width(), last_pos.y() + element_size.height()};

          current_line.size.width() = std::max(current_line.size.width(), element_size.width());
          current_line.size.height() = end_pos.height();

          out.max_pos.x() = std::max(out.max_pos.x(), end_pos.width());
          out.max_pos.y() = std::max(out.max_pos.y(), end_pos.height());

          last_pos.y() += element_size.height();
          last_pos.y() += distance.height();

          out.max_count_in_v_line = std::max(out.max_count_in_v_line, current_line.frames.size());

          break;
        }

        default:
          break;
      }
    }

    out.lines.push_back(current_line);
  };

  build_information info;
  update(size, distance, info);

  Size content_size{info.max_pos - info.min_pos};
  Size available_space{size - content_size};
  Size offset{0, 0};

  Size max_distance;

  if (info.max_count_in_h_line > 1)
    max_distance.set_width(distance.width() +
                           available_space.width() / (info.max_count_in_h_line - 1));

  if (info.max_count_in_v_line > 1)
    max_distance.set_height(distance.height() +
                            available_space.height() / (info.max_count_in_v_line - 1));

  if (horizontal_alignment_ == Alignment::between) {
    info = {};
    update(size, {max_distance.width(), distance.height()}, info);
  }

  if (vertical_alignment_ == Alignment::between) {
    info = {};
    update(size, {distance.width(), max_distance.height()}, info);
  }

  if (direction_ == Direction::horizontal && vertical_alignment_ == Alignment::center)
    offset.height() = (size.height() - content_size.height()) / 2;
  else if (direction_ == Direction::vertical && horizontal_alignment_ == Alignment::center)
    offset.width() = (size.width() - content_size.width()) / 2;

  for (const auto& line : info.lines) {
    for (Frame* frame : line.frames) {
      Size new_offset{offset};

      if (direction_ == Direction::horizontal) {
        if (vertical_alignment_ == Alignment::center)
          new_offset.height() += (line.size.height() - frame->size().height()) / 2;
        if (horizontal_alignment_ == Alignment::center)
          new_offset.width() += (size.width() - line.size.width()) / 2;

        if (vertical_alignment_ == Alignment::end)
          new_offset.height() += size.height() - line.size.height();
        if (horizontal_alignment_ == Alignment::end)
          new_offset.width() += size.width() - line.size.width();
      }

      if (direction_ == Direction::vertical) {
        if (vertical_alignment_ == Alignment::center)
          new_offset.height() += (size.height() - line.size.height()) / 2;
        if (horizontal_alignment_ == Alignment::center)
          new_offset.width() += (line.size.width() - frame->size().width()) / 2;

        if (vertical_alignment_ == Alignment::end)
          new_offset.height() += size.height() - line.size.height();
        if (horizontal_alignment_ == Alignment::end)
          new_offset.width() += size.width() - frame->size().width();
      }

      frame->move(frame->position() + new_offset);
    }
  }
}

leetui::Size leetui::FlexLayout::padding() const {
  return padding_;
}

leetui::Size leetui::FlexLayout::distance() const {
  return distance_;
}

leetui::FlexLayout::Direction leetui::FlexLayout::direction() const {
  return direction_;
}

bool leetui::FlexLayout::wrap() const {
  return wrap_;
}

leetui::FlexLayout::Alignment leetui::FlexLayout::vertical_alignment() const {
  return vertical_alignment_;
}

leetui::FlexLayout::Alignment leetui::FlexLayout::horizontal_alignment() const {
  return horizontal_alignment_;
}

void leetui::FlexLayout::set_padding(const Size& padding) {
  padding_ = padding;
}

void leetui::FlexLayout::set_distance(const Size& distance) {
  distance_ = distance;
}

void leetui::FlexLayout::set_direction(Direction direction) {
  direction_ = direction;
}

void leetui::FlexLayout::set_wrap(bool value) {
  wrap_ = value;
}

void leetui::FlexLayout::set_vertical_alignment(Alignment alignment) {
  vertical_alignment_ = alignment;
}

void leetui::FlexLayout::set_horizontal_alignment(Alignment alignment) {
  horizontal_alignment_ = alignment;
}
