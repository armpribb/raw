#pragma once

#include <memory>

#include "types.h"

namespace convert {

class interface {
public:
  virtual ~interface() = default;
  virtual void run() const = 0;
};

std::unique_ptr<convert::interface> get_converter(const parse_result &config,
                                                  queue_func _print = none);

} // namespace convert
