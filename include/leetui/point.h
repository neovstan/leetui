#ifndef LEETUI_POINT_H
#define LEETUI_POINT_H

namespace leetui {
class Size;

class Point {
 public:
  Point();
  Point(double x, double y);

  double x() const;
  double y() const;

  double& x();
  double& y();

  void set_x(double value);
  void set_y(double value);

  bool is_in_rectangle(const Point& p, const Size& size) const;
  bool is_between_points(const Point& p1, const Point& p2) const;

  void operator+=(const Point& rhs);
  void operator-=(const Point& rhs);

  operator bool() const;

 private:
  double x_;
  double y_;
  bool inf_;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
}  // namespace leetui

#endif  // LEETUI_POINT_H
