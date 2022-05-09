#pragma once

#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace format {

class interface {
public:
  virtual ~interface() = default;
  virtual std::string process(const std::vector<uint8_t> &raw_data) const = 0;
};

std::unique_ptr<format::interface>
get_format_engine(const format_config &config = {});

} // namespace format
