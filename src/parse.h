#pragma once

#include <memory>

#include "types.h"

namespace parse {

class interface {
public:
  interface() = default;
  virtual ~interface() = default;
  virtual parse_result do_parse(int argc, char **argv) = 0;

protected:
  interface(const interface&) = default;
  interface(interface&&) = default;
  interface& operator=(const interface&) = default;
  interface& operator=(interface&&) = default;
};

std::unique_ptr<parse::interface> get_parser(queue_func _queue = none);

} // namespace parse
