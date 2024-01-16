#include "corner.h"

leetui::Corner::Corner() : top_left_{}, top_right_{}, bottom_right_{}, bottom_left_{} {
}

leetui::Corner::Corner(double all)
    : top_left_{all}, top_right_{all}, bottom_right_{all}, bottom_left_{all} {
}

leetui::Corner::Corner(double top_left, double bottom_right)
    : top_left_{top_left},
      top_right_{bottom_right_},
      bottom_right_{top_left},
      bottom_left_{bottom_right_} {
}

leetui::Corner::Corner(double top_left, double top_right, double bottom_right, double bottom_left)
    : top_left_{top_left},
      top_right_{top_right},
      bottom_right_{bottom_right},
      bottom_left_{bottom_left} {
}

double leetui::Corner::top_left() const {
  return top_left_;
}

double leetui::Corner::top_right() const {
  return top_right_;
}

double leetui::Corner::bottom_right() const {
  return bottom_right_;
}

double leetui::Corner::bottom_left() const {
  return bottom_left_;
}

double& leetui::Corner::top_left() {
  return top_left_;
}

double& leetui::Corner::top_right() {
  return top_right_;
}

double& leetui::Corner::bottom_right() {
  return bottom_right_;
}

double& leetui::Corner::bottom_left() {
  return bottom_left_;
}

void leetui::Corner::set_top_left(double value) {
  top_left_ = value;
}

void leetui::Corner::set_top_right(double value) {
  top_right_ = value;
}

void leetui::Corner::set_bottom_right(double value) {
  bottom_right_ = value;
}

void leetui::Corner::set_bottom_left(double value) {
  bottom_left_ = value;
}
