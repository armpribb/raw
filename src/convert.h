#pragma once

#include <memory>

#include "types.h"

namespace convert {

class interface {
public:
  interface() = default;
  virtual ~interface() = default;
  virtual void run() const = 0;

protected:
  interface(const interface &) = default;
  interface(interface &&) = default;
  interface &operator=(const interface &) = default;
  interface &operator=(interface &&) = default;
};

std::unique_ptr<convert::interface>
get_converter(const parse_result &config, std::unique_ptr<ios_abstract> ios,
              print_func print = _none);

} // namespace convert
