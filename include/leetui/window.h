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
#include "tree.h"

namespace leetui {
class Frame;

class Window {
  friend class Frame;
  friend class Tree;

 public:
  Window(std::unique_ptr<Painter> painter, std::unique_ptr<Controller> controller);

 public:
  Point position() const;
  Size size() const;
  Controller* controller() const;

 public:
  void move(const Point& p);
  void resize(const Size& size);

 public:
  void process();

 public:
  void add_font(const std::string& name, const std::string& resource, double size);
  void add_image(const std::string& name, const std::string& resource);
  void add_movie(const std::string& name, const std::string& resource);

 public:
  Font get_font(const std::string& name) const;
  Image get_image(const std::string& name) const;
  Movie get_movie(const std::string& name) const;

 protected:
  Painter* painter() const;

 protected:
  void add_frame(Frame* frame);
  void remove_frame(Frame* frame);

 private:
  void draw_frame(const Point& abs_pos, double opacity, Frame* frame) const;
  void draw_label(Point abs_pos, double opacity, Label* label) const;

 private:
  void mouse_button_down(const Point& p, Controller::MouseButton button);
  void mouse_button_up(const Point& p, Controller::MouseButton button);
  void mouse_move(const Point& p);
  void mouse_wheel(double delta);

 private:
  void key_down(const Key& key);
  void key_up(const Key& key);

 private:
  std::unique_ptr<Painter> painter_;
  std::unique_ptr<Controller> controller_;
  Point position_;
  Size size_;

 private:
  Tree tree_;
  std::vector<MouseAction> clicks_;
  std::vector<MouseAction> presses_;
  std::unordered_map<std::string, Font> fonts_;
  std::unordered_map<std::string, Image> images_;
  std::unordered_map<std::string, Movie> movies_;

 private:
  struct {
    Point pos;
    std::unordered_map<Controller::MouseButton, bool> button_state;
  } mouse_;
};
}  // namespace leetui

#endif  // LEETUI_WINDOW_H
