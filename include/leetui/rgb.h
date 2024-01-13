#ifndef LEETUI_RGB_H
#define LEETUI_RGB_H

namespace leetui {
class Rgb {
 public:
  Rgb(int r, int g, int b, int a = 255);
  Rgb(unsigned int argb);

  int r() const;
  int g() const;
  int b() const;
  int a() const;

  int& r();
  int& g();
  int& b();
  int& a();

  Rgb set_r(int r) const;
  Rgb set_g(int g) const;
  Rgb set_b(int b) const;
  Rgb set_a(int a) const;

  Rgb& set_r(int r);
  Rgb& set_g(int g);
  Rgb& set_b(int b);
  Rgb& set_a(int a);

  operator unsigned int() const;

 private:
  int r_;
  int g_;
  int b_;
  int a_;
};

bool operator==(const Rgb& lhs, const Rgb& rhs);
bool operator!=(const Rgb& lhs, const Rgb& rhs);
}  // namespace leetui

#endif  // LEETUI_RGB_H
