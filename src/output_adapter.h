#pragma once

#include <memory>
#include <string>

#include "types.h"

namespace output {

class interface {
public:
  virtual ~interface() = default;
  virtual const char *info() const = 0;
  virtual void write(const std::string &str) const = 0;
};

std::unique_ptr<output::interface> get_output_adapter(output_type type);

} // namespace output
