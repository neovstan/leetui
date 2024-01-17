#ifndef LEETUI_CORNER_H
#define LEETUI_CORNER_H

namespace leetui {
class Corner {
 public:
  Corner();
  Corner(double all);
  Corner(double top_left, double bottom_right);
  Corner(double top_left, double top_right, double bottom_right, double bottom_left);

  double top_left() const;
  double top_right() const;
  double bottom_right() const;
  double bottom_left() const;

  double& top_left();
  double& top_right();
  double& bottom_right();
  double& bottom_left();

  void set_top_left(double value);
  void set_top_right(double value);
  void set_bottom_right(double value);
  void set_bottom_left(double value);

 private:
  double top_left_;
  double top_right_;
  double bottom_right_;
  double bottom_left_;
};
}  // namespace leetui

#endif  // LEETUI_CORNER_H
