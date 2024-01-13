#include "rgb.h"

const int r_shift = 0;
const int g_shift = 8;
const int b_shift = 16;
const int a_shift = 24;

leetui::Rgb::Rgb(int r, int g, int b, int a) : r_{r}, g_{g}, b_{b}, a_{a} {
}

leetui::Rgb::Rgb(unsigned int argb)
    : r_{(argb >> r_shift) & 0xFF},
      g_{(argb >> g_shift) & 0xFF},
      b_{(argb >> b_shift) & 0xFF},
      a_{(argb >> a_shift) & 0xFF} {
}

int leetui::Rgb::r() const {
  return r_;
}

int leetui::Rgb::g() const {
  return g_;
}

int leetui::Rgb::b() const {
  return b_;
}

int leetui::Rgb::a() const {
  return a_;
}

int& leetui::Rgb::r() {
  return r_;
}

int& leetui::Rgb::g() {
  return g_;
}

int& leetui::Rgb::b() {
  return b_;
}

int& leetui::Rgb::a() {
  return a_;
}

leetui::Rgb leetui::Rgb::set_r(int r) const {
  return Rgb{r, g_, b_, a_};
}

leetui::Rgb leetui::Rgb::set_g(int g) const {
  return Rgb{r_, g, b_, a_};
}

leetui::Rgb leetui::Rgb::set_b(int b) const {
  return Rgb{r_, g_, b, a_};
}

leetui::Rgb leetui::Rgb::set_a(int a) const {
  return Rgb{r_, g_, b_, a};
}

leetui::Rgb& leetui::Rgb::set_r(int r) {
  r_ = r;
  return *this;
}

leetui::Rgb& leetui::Rgb::set_g(int g) {
  g_ = g;
  return *this;
}

leetui::Rgb& leetui::Rgb::set_b(int b) {
  b_ = b;
  return *this;
}

leetui::Rgb& leetui::Rgb::set_a(int a) {
  a_ = a;
  return *this;
}

leetui::Rgb::operator unsigned int() const {
  unsigned int out = 0;
  out = r_ << r_shift;
  out |= g_ << g_shift;
  out |= b_ << b_shift;
  out |= a_ << a_shift;
  return out;
}

bool leetui::operator==(const Rgb& lhs, const Rgb& rhs) {
  return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() && lhs.a() == rhs.a();
}

bool leetui::operator!=(const Rgb& lhs, const Rgb& rhs) {
  return !(lhs == rhs);
}
