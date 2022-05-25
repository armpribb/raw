#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace input {

class interface {
public:
  virtual ~interface() = default;
  virtual const char *info() const = 0;
  virtual std::vector<uint8_t> read() const = 0;
};

std::unique_ptr<input::interface>
get_input_adapter(input_type type, const std::vector<std::string> &input = {});

bool _internal_set(input::interface &instance, const char *c_str);

} // namespace input
