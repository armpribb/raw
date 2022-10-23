#pragma once

#include "types.h"

#include <memory>

namespace parse {

class interface {
public:
  interface() = default;
  virtual ~interface() = default;
  virtual convert_config do_parse(int argc, char **argv) = 0;

protected:
  interface(const interface &) = default;
  interface(interface &&) = default;
  interface &operator=(const interface &) = default;
  interface &operator=(interface &&) = default;
};

std::unique_ptr<parse::interface>
get_parser(const print_func &print = set_none);

} // namespace parse
