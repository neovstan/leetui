#ifndef LEETUI_RESOURCE_H
#define LEETUI_RESOURCE_H

#include <unordered_map>
#include <string>
#include <cstdint>

namespace leetui {
using raw_data_t = std::uint8_t*;

struct Resource {
  raw_data_t data;
  std::uint64_t size;
};

class Resources {
  Resources();

 public:
  Resources(Resources&&) = delete;
  Resources(const Resources&) = delete;

  void set(const std::string& key, raw_data_t data, std::uint64_t size);

  template <std::uint64_t Size>
  void set(const std::string& key, const std::uint8_t (&data)[Size]) {
    set(key, raw_data_t(data), Size);
  }

  Resource get(const std::string& key) const;

  static Resources& instance();

 private:
  std::unordered_map<std::string, Resource> data_;
};
}  // namespace leetui

#endif  // LEETUI_RESOURCE_H
