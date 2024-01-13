#ifndef LEETUI_COND_BEHAVIOR_H
#define LEETUI_COND_BEHAVIOR_H

#include <string>
#include <functional>
#include <vector>
#include <chrono>

#include "signal.h"
#include "easing_curves.h"

namespace leetui {
class Frame;

class CondBehavior {
  using time_point_t = std::chrono::steady_clock::time_point;

 public:
  using tendention_easing_curve_t = std::function<double(double progress)>;
  using tendention_implier_t = std::function<void(double value)>;
  using predicate_t = std::function<bool(double value)>;

 private:
  struct Predicate {
    std::string param;
    predicate_t predicate;
    bool parental;
  };

  struct Tendention {
    std::string param;
    double start_value;
    double end_value;
    tendention_easing_curve_t easing_curve;
    tendention_implier_t implier;
    bool parental;
  };

 public:
  CondBehavior(Frame* frame);
  virtual ~CondBehavior();

 public:
  void set_predicate(const std::string& param, predicate_t predicate, bool parental = false);
  void set_duration(double duration);
  void add_tendention(const std::string& param, double end_value,
                      tendention_easing_curve_t easing_curve, tendention_implier_t implier,
                      bool parental = false);

 private:
  void process();

 private:
  Frame* frame_;
  Predicate predicate_;
  double duration_;
  std::vector<Tendention> tendentions_;
  double param_inf_;
  bool prev_predicate_result_;
  time_point_t last_time_;
  slot_key_t slot_key_;
};
}  // namespace leetui

#endif  // LEETUI_COND_BEHAVIOR_H
