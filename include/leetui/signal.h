#ifndef LEETUI_SIGNAL_H
#define LEETUI_SIGNAL_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <cstdint>

namespace leetui {
using slot_key_t = std::uint64_t;

template <class T>
class Signal {
  using slot_t = std::function<T>;

 public:
  slot_key_t connect(slot_t slot) {
    const auto key = ++max_key_;
    slots_to_connect_[key] = slot;
    return key;
  }

  void disconnect(slot_key_t key) {
    slots_to_disconnect_.push_back(key);
  }

  template <class... Args>
  void emit(Args&&... args) {
    for (const auto& slot : slots_to_connect_) {
      slots_[slot.first] = slot.second;
    }

    for (const auto key : slots_to_disconnect_) {
      slots_.erase(key);
    }

    slots_to_connect_ = {};
    slots_to_disconnect_ = {};

    for (const auto& slot : slots_) {
      slot.second(std::forward<Args>(args)...);
    }
  }

 private:
  std::unordered_map<slot_key_t, slot_t> slots_to_connect_;
  std::vector<slot_key_t> slots_to_disconnect_;
  std::unordered_map<slot_key_t, slot_t> slots_;
  slot_key_t max_key_{};
};
}  // namespace leetui

#endif  // LEETUI_SIGNAL_H
