#pragma once

#include <memory>

#include "types.h"

namespace parse {

class interface {
public:
  virtual ~interface() = default;
  virtual parse_result do_parse(int argc, char **argv) = 0;
};

std::unique_ptr<parse::interface> get_parser(queue_func _queue = none);

} // namespace parse
