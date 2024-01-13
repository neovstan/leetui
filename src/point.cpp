#include "point.h"

#include "size.h"

leetui::Point::Point() : x_{}, y_{}, inf_{true} {
}

leetui::Point::Point(double x, double y) : x_{x}, y_{y}, inf_{false} {
}

double leetui::Point::x() const {
  return x_;
}

double leetui::Point::y() const {
  return y_;
}

double& leetui::Point::x() {
  return x_;
}

double& leetui::Point::y() {
  return y_;
}

void leetui::Point::set_x(double value) {
  inf_ = false;
  x_ = value;
}

void leetui::Point::set_y(double value) {
  inf_ = false;
  y_ = value;
}

bool leetui::Point::is_in_rectangle(const Point& p, const Size& size) const {
  return x() >= p.x() && x() <= p.x() + size.width() && y() >= p.y() &&
         y() <= p.y() + size.height();
}

bool leetui::Point::is_between_points(const Point& p1, const Point& p2) const {
  return x() >= p1.x() && x() <= p2.x() && y() >= p1.y() && y() <= p2.y();
}

leetui::Point::operator bool() const {
  return !inf_;
}

bool leetui::operator==(const Point& lhs, const Point& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

bool leetui::operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs == rhs);
}

leetui::Point leetui::operator+(const Point& lhs, const Point& rhs) {
  return Point{lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

leetui::Point leetui::operator-(const Point& lhs, const Point& rhs) {
  return Point{lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}
