#include "cond_behavior.h"

#include <algorithm>

#include "frame.h"

leetui::CondBehavior::CondBehavior(Frame* frame)
    : frame_{frame},
      predicate_{},
      duration_{},
      tendentions_{},
      param_inf_{1e12},
      prev_predicate_result_{},
      last_time_{},
      slot_key_{} {
  frame_->cond_behaviors_.push_back(this);
  slot_key_ = frame_->process.connect([this]() { process(); });
}

leetui::CondBehavior::~CondBehavior() {
  frame_->process.disconnect(slot_key_);
  auto& cb = frame_->cond_behaviors_;
  auto it = std::find(cb.begin(), cb.end(), this);
  if (it != cb.end()) cb.erase(it);
}

void leetui::CondBehavior::set_predicate(const std::string& param, predicate_t predicate,
                                         bool parental) {
  predicate_.param = param;
  predicate_.predicate = predicate;
  predicate_.parental = parental;

  const auto pred_frame = predicate_.parental ? frame_->parent() : frame_;
  const auto current_value = pred_frame->param(predicate_.param);
  prev_predicate_result_ = predicate(current_value);
}

void leetui::CondBehavior::set_duration(double duration) {
  duration_ = duration;
}

void leetui::CondBehavior::add_tendention(const std::string& param, double end_value,
                                          tendention_easing_curve_t easing_curve,
                                          tendention_implier_t implier, bool parental) {
  Tendention tendention{param, param_inf_, end_value, easing_curve, implier, parental};
  tendentions_.push_back(tendention);
}

void leetui::CondBehavior::process() {
  using namespace std::chrono;

  const auto pred_frame = predicate_.parental ? frame_->parent() : frame_;
  const auto current_value = pred_frame->param(predicate_.param);
  const auto predicate_result = predicate_.predicate(current_value);

  if (predicate_result && !prev_predicate_result_) {
    last_time_ = steady_clock::now();
    for (auto& tendention : tendentions_) {
      auto frame = tendention.parental ? frame_->parent() : frame_;
      tendention.start_value = frame->param(tendention.param);
    }
  }

  prev_predicate_result_ = predicate_result;
  if (!predicate_result) return;

  for (const auto& tendention : tendentions_) {
    const double elapsed{0.001 *
                         duration_cast<milliseconds>(steady_clock::now() - last_time_).count()};

    double progress{elapsed / duration_};
    progress = std::min(progress, 1.0);

    const auto interval = tendention.end_value - tendention.start_value;
    const auto value = tendention.start_value + interval * tendention.easing_curve(progress);

    tendention.implier(value);

    auto frame = tendention.parental ? frame_->parent() : frame_;
    frame->set_param(tendention.param, value);
  }
}
