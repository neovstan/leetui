#ifndef LEETUI_RESOURCE_H
#define LEETUI_RESOURCE_H

#include <cstdint>
#include <string>
#include <unordered_map>

namespace leetui {
using raw_data_t = const char*;

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

  Resource get(const std::string& key) const;

  static Resources& instance();

 private:
  std::unordered_map<std::string, Resource> data_;
};
}  // namespace leetui

#endif  // LEETUI_RESOURCE_H
