#include "resource.h"

leetui::Resources::Resources() {
}

void leetui::Resources::set(const std::string& key, raw_data_t data, std::uint64_t size) {
  data_[key] = {data, size};
}

leetui::Resource leetui::Resources::get(const std::string& key) const {
  return data_.at(key);
}

leetui::Resources& leetui::Resources::instance() {
  static Resources instance;
  return instance;
}
