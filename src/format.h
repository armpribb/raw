#pragma once

#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace format {
class engine {
public:
  engine() = default;
  engine(const format_config &cnf) : config(cnf){};
  ~engine() = default;

  std::string process(const std::vector<uint8_t> &raw_data) const;

private:
  format_config config{};
};

std::unique_ptr<format::engine> get_format_engine(const format_config &config);

} // namespace format
