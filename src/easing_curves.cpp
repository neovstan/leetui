#include "easing_curves.h"

#define _USE_MATH_DEFINES
#include <math.h>

double leetui::line(double x) {
  return x;
}

double leetui::ease_in_sine(double x) {
  return 1 - cos((x * M_PI) / 2);
}

double leetui::ease_out_sine(double x) {
  return sin((x * M_PI) / 2);
}

double leetui::ease_in_out_sine(double x) {
  return -(cos(M_PI * x) - 1) / 2;
}

double leetui::ease_in_cubic(double x) {
  return x * x * x;
}

double leetui::ease_out_cubic(double x) {
  return 1 - pow(1 - x, 3);
}

double leetui::ease_in_out_cubic(double x) {
  return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}

double leetui::ease_in_quint(double x) {
  return x * x * x * x * x;
}

double leetui::ease_out_quint(double x) {
  return 1 - pow(1 - x, 5);
}

double leetui::ease_in_out_quint(double x) {
  return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

double leetui::ease_in_circ(double x) {
  return 1 - sqrt(1 - pow(x, 2));
}

double leetui::ease_out_circ(double x) {
  return sqrt(1 - pow(x - 1, 2));
}

double leetui::ease_in_out_circ(double x) {
  return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}

double leetui::ease_in_elastic(double x) {
  const auto c4 = (2 * M_PI) / 3;

  return x == 0 ? 0 : x == 1 ? 1 : -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
}

double leetui::ease_out_elastic(double x) {
  const auto c4 = (2 * M_PI) / 3;

  return x == 0 ? 0 : x == 1 ? 1 : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}

double leetui::ease_in_out_elastic(double x) {
  const auto c5 = (2 * M_PI) / 4.5;

  return x == 0    ? 0
         : x == 1  ? 1
         : x < 0.5 ? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
                   : (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
}

double leetui::ease_in_quad(double x) {
  return x * x;
}

double leetui::ease_out_quad(double x) {
  return 1 - (1 - x) * (1 - x);
}

double leetui::ease_in_out_quad(double x) {
  return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}

double leetui::ease_in_quart(double x) {
  return x * x * x * x;
}

double leetui::ease_out_quart(double x) {
  return 1 - pow(1 - x, 4);
}

double leetui::ease_in_out_quart(double x) {
  return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
}

double leetui::ease_in_expo(double x) {
  return x == 0 ? 0 : pow(2, 10 * x - 10);
}

double leetui::ease_out_expo(double x) {
  return x == 1 ? 1 : 1 - pow(2, -10 * x);
}

double leetui::ease_in_out_expo(double x) {
  return x == 0    ? 0
         : x == 1  ? 1
         : x < 0.5 ? pow(2, 20 * x - 10) / 2
                   : (2 - pow(2, -20 * x + 10)) / 2;
}

double leetui::ease_in_back(double x) {
  const auto c1 = 1.70158;
  const auto c3 = c1 + 1;

  return c3 * x * x * x - c1 * x * x;
}

double leetui::ease_out_back(double x) {
  const auto c1 = 1.70158;
  const auto c3 = c1 + 1;

  return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}

double leetui::ease_in_out_back(double x) {
  const auto c1 = 1.70158;
  const auto c2 = c1 * 1.525;

  return x < 0.5 ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
                 : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

double leetui::ease_in_bounce(double x) {
  return 1 - ease_out_bounce(1 - x);
}

double leetui::ease_out_bounce(double x) {
  const auto n1 = 7.5625;
  const auto d1 = 2.75;

  if (x < 1 / d1) {
    return n1 * x * x;
  } else if (x < 2 / d1) {
    return n1 * (x -= 1.5 / d1) * x + 0.75;
  } else if (x < 2.5 / d1) {
    return n1 * (x -= 2.25 / d1) * x + 0.9375;
  } else {
    return n1 * (x -= 2.625 / d1) * x + 0.984375;
  }
}

double leetui::ease_in_out_bounce(double x) {
  return x < 0.5 ? (1 - ease_out_bounce(1 - 2 * x)) / 2 : (1 + ease_out_bounce(2 * x - 1)) / 2;
}
