#ifndef LEETUI_SIZE_H
#define LEETUI_SIZE_H

namespace leetui {
class Point;

class Size {
 public:
  Size();
  Size(double width, double height);
  explicit Size(const Point& point);

  double width() const;
  double height() const;

  double& width();
  double& height();

  void set_width(double value);
  void set_height(double value);

  operator bool() const;
  bool operator>(const Size& rhs) const;
  bool operator<(const Size& rhs) const;

  Size& operator+=(const Size& rhs);
  Size& operator-=(const Size& rhs);
  Size& operator*=(const Size& rhs);
  Size& operator/=(const Size& rhs);

  Size& operator*=(double rhs);
  Size& operator/=(double rhs);

  operator leetui::Point() const;

 private:
  double width_;
  double height_;
  bool inf_;
};

Size operator+(const Size& lhs, const Size& rhs);
Size operator-(const Size& lhs, const Size& rhs);
Size operator*(const Size& lhs, const Size& rhs);
Size operator/(const Size& lhs, const Size& rhs);

Size operator*(const Size& lhs, double rhs);
Size operator/(const Size& lhs, double rhs);

bool operator==(const Size& lhs, const Size& rhs);
bool operator!=(const Size& lhs, const Size& rhs);
}  // namespace leetui

#endif  // LEETUI_SIZE_H
