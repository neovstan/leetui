#ifndef LEETUI_KEYBOARD_H
#define LEETUI_KEYBOARD_H

#include <map>
#include <string>

namespace leetui {
class Key {
 public:
  Key(int code, const std::string& name, bool is_char = false);

  int code() const;
  std::string name() const;
  bool is_char() const;

  static int invalid();

  operator bool() const;

 private:
  int code_;
  std::string name_;
  bool is_char_;
};

static bool operator>(const Key& lhs, const Key& rhs);
static bool operator<(const Key& lhs, const Key& rhs);
static bool operator==(const Key& lhs, const Key& rhs);

class Keyboard {
 public:
  bool set(const Key& key, int controller_code);
  int get(const Key& key) const;
  Key get(int impl_key) const;

 private:
  std::map<Key, int> keys_;
};
}  // namespace leetui

#endif  // LEETUI_KEYBOARD_H
