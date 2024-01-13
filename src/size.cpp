#include "size.h"

leetui::Size::Size() : width_{}, height_{}, inf_{true} {
}

leetui::Size::Size(double width, double height) : width_{width}, height_{height}, inf_{false} {
}

double leetui::Size::width() const {
  return width_;
}

double leetui::Size::height() const {
  return height_;
}

double& leetui::Size::width() {
  inf_ = false;
  return width_;
}

double& leetui::Size::height() {
  inf_ = false;
  return height_;
}

void leetui::Size::set_width(double value) {
  inf_ = false;
  width_ = value;
}

void leetui::Size::set_height(double value) {
  inf_ = false;
  height_ = value;
}

leetui::Size::operator bool() const {
  return !inf_;
}

bool leetui::Size::operator>(const Size& rhs) const {
  return width() * height() > rhs.width() * rhs.height();
}

bool leetui::Size::operator<(const Size& rhs) const {
  return rhs > *this;
}

leetui::Size& leetui::Size::operator+=(const Size& rhs) {
  *this = *this + rhs;
  return *this;
}

leetui::Size& leetui::Size::operator-=(const Size& rhs) {
  *this = *this - rhs;
  return *this;
}

leetui::Size& leetui::Size::operator*=(const Size& rhs) {
  *this = *this * rhs;
  return *this;
}

leetui::Size& leetui::Size::operator/=(const Size& rhs) {
  *this = *this / rhs;
  return *this;
}

leetui::Size& leetui::Size::operator*=(double rhs) {
  *this = *this * rhs;
  return *this;
}

leetui::Size& leetui::Size::operator/=(double rhs) {
  *this = *this / rhs;
  return *this;
}

bool leetui::operator==(const Size& lhs, const Size& rhs) {
  return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

bool leetui::operator!=(const Size& lhs, const Size& rhs) {
  return !(lhs == rhs);
}

leetui::Size leetui::operator+(const Size& lhs, const Size& rhs) {
  return {lhs.width() + rhs.width(), lhs.height() + rhs.height()};
}

leetui::Size leetui::operator-(const Size& lhs, const Size& rhs) {
  return {lhs.width() - rhs.width(), lhs.height() - rhs.height()};
}

leetui::Size leetui::operator*(const Size& lhs, const Size& rhs) {
  return {lhs.width() * rhs.width(), lhs.height() * rhs.height()};
}

leetui::Size leetui::operator/(const Size& lhs, const Size& rhs) {
  return {lhs.width() / rhs.width(), lhs.height() / rhs.height()};
}

leetui::Size leetui::operator*(const Size& lhs, double rhs) {
  return {lhs.width() * rhs, lhs.height() * rhs};
}

leetui::Size leetui::operator/(const Size& lhs, double rhs) {
  return {lhs.width() / rhs, lhs.height() / rhs};
}
