#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace format {
struct config {
  bool use_hex_prefix{false};
  bool use_uppercase{false};
  uint8_t n_byte_group{1};
  std::string byte_separator{" "};
};

class engine {
public:
  engine() = default;
  engine(const format::config &cnf) : config(cnf){};
  ~engine() = default;

  std::string process(const std::vector<uint8_t> &raw_data) const;

private:
  format::config config{};
};
} // namespace format
