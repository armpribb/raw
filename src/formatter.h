#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace format {
class engine {
public:
  engine() = default;
  engine(bool prefix, bool uppercase, const std::string &separator)
      : use_hex_prefix(prefix), use_uppercase(uppercase),
        byte_separator(separator){};
  ~engine() = default;

  std::string process(const std::vector<uint8_t> &raw_data) const;

private:
  bool use_hex_prefix{false};
  bool use_uppercase{false};
  std::string byte_separator{" "};
};
} // namespace format
