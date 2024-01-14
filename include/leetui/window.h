#ifndef LEETUI_WINDOW_H
#define LEETUI_WINDOW_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "controller.h"
#include "font.h"
#include "image.h"
#include "label.h"
#include "mouse_action.h"
#include "movie.h"
#include "painter.h"
#include "point.h"
#include "size.h"

namespace leetui {
class Frame;

class Window {
  friend class Frame;

 public:
  Window(std::unique_ptr<Painter> painter, std::unique_ptr<Controller> controller);

  Point position() const;
  Size size() const;

  void move(const Point& p);
  void resize(const Size& size);

  void process();

  void add_font(const std::string& name, const std::string& resource, double size);
  void add_image(const std::string& name, const std::string& resource);
  void add_movie(const std::string& name, const std::string& resource);

  Font get_font(const std::string& name) const;
  Image get_image(const std::string& name) const;
  Movie get_movie(const std::string& name) const;

  Controller* controller() const;

 protected:
  Painter* painter() const;
  void add_frame(Frame* parent, Frame* child);
  void remove_frame(Frame* parent, Frame* child);

 private:
  void draw_frame(Point cs, int min_alpha, Frame* frame) const;
  void draw_label(Point cs, int min_alpha, Label* label) const;

 private:
  void mouse_button_down(const Point& p, Controller::MouseButton button);
  void mouse_button_up(const Point& p, Controller::MouseButton button);
  void mouse_move(const Point& p);
  void mouse_wheel(double delta);
  void key_down(const Key& key);
  void key_up(const Key& key);

 private:
  std::unique_ptr<Painter> painter_;
  std::unique_ptr<Controller> controller_;
  std::unordered_map<Frame*, std::vector<Frame*>> frames_tree_;
  std::vector<MouseAction> clicks_;
  std::vector<MouseAction> presses_;
  Point mouse_pos_;
  Frame* hovered_frame_;
  Frame* focus_frame_;
  std::unordered_map<std::string, Font> fonts_;
  std::unordered_map<std::string, Image> images_;
  std::unordered_map<std::string, Movie> movies_;
  std::unordered_map<Controller::MouseButton, bool> mouse_button_state_;

 private:
  Point position_;
  Size size_;
};
}  // namespace leetui

#endif  // LEETUI_WINDOW_H
