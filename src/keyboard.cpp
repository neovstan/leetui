#include "keyboard.h"

leetui::Key::Key(int code, const std::string& name, bool is_char)
    : code_{code}, name_{name}, is_char_{is_char} {
}

int leetui::Key::code() const {
  return code_;
}

std::string leetui::Key::name() const {
  return name_;
}

bool leetui::Key::is_char() const {
  return is_char_;
}

int leetui::Key::invalid() {
  return -1;
}

leetui::Key::operator bool() const {
  return code_ != invalid();
}

bool leetui::operator>(const Key& lhs, const Key& rhs) {
  return lhs.code() > rhs.code();
}

bool leetui::operator<(const Key& lhs, const Key& rhs) {
  return lhs.code() < rhs.code();
}

bool leetui::operator==(const Key& lhs, const Key& rhs) {
  return lhs.code() == rhs.code();
}

bool leetui::Keyboard::set(const Key& key, int controller_code) {
  if (controller_code != Key::invalid()) {
    keys_[key] = controller_code;
    return true;
  }
  return false;
}

int leetui::Keyboard::get(const Key& key) const {
  if (!keys_.count(key)) return Key::invalid();
  return keys_.at(key);
}

leetui::Key leetui::Keyboard::get(int impl_key) const {
  for (auto& key : keys_) {
    if (key.second == impl_key) return key.first;
  }
  return {Key::invalid(), ""};
}
