#ifndef LEETUI_FRAME_H
#define LEETUI_FRAME_H

#include <unordered_map>

#include "color.h"
#include "controller.h"
#include "movie.h"
#include "painter.h"
#include "point.h"
#include "signal.h"
#include "size.h"

namespace leetui {
class Window;
class Layout;
class Resource;
class CondBehavior;

class Frame {
  friend class CondBehavior;

 public:
  explicit Frame(Window* window);
  explicit Frame(Frame* parent);

  virtual ~Frame();

 public:
  Window* window() const;
  Frame* parent() const;
  Point position() const;
  Size size() const;
  Color color() const;
  bool visible() const;
  bool active() const;
  double rounding() const;
  Layout* layout() const;
  bool label() const;
  Painter::native_texture_t texture() const;
  double param(const std::string& key);
  bool transparent() const;
  int alpha() const;
  bool popup() const;

 public:
  operator bool() const;

 public:
  void move(const Point& position);
  void resize(const Size& size);

 public:
  void show();
  void hide();
  Frame* deepen(int depth);

 public:
  void set_color(const Color& color);
  void set_alpha(int alpha);
  void set_active(bool active);
  void set_rounding(double rounding);
  void set_layout(Layout* layout);
  void set_image(const std::string& image);
  void set_movie(const std::string& movie);
  void set_param(const std::string& key, double value);
  void set_transparent(bool transparent);
  void set_popup(bool popup);

 public:
  Signal<void(const Point&, Controller::MouseButton)> clicked;
  Signal<void(const Point&, Controller::MouseButton)> pressed;
  Signal<void(const Point&)> hover;
  Signal<void(double)> wheel;
  Signal<void()> came_in_hover;
  Signal<void()> out_of_hover;
  Signal<void()> came_in_focus;
  Signal<void()> out_of_focus;
  Signal<void(const Key&)> key_down;
  Signal<void(const Key&)> key_up;
  Signal<void()> process;

 protected:
  Window* window_;
  Frame* parent_;
  Point position_;
  Size size_;
  Color color_;
  bool visible_;
  bool active_;
  double rounding_;
  Layout* layout_;
  bool label_;
  Painter::native_texture_t texture_;
  Movie movie_;
  std::unordered_map<std::string, double> params_;
  std::vector<CondBehavior*> cond_behaviors_;
  bool transparent_;
  bool popup_;
};
}  // namespace leetui

#endif  // LEETUI_FRAME_H
