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

std::unique_ptr<convert::interface> get_converter(const convert_config &config,
                                                  stream_provider &ios,
                                                  print_func print = set_none);

std::unique_ptr<convert::interface>
get_converter_v2(const convert_config_v2 &config);

} // namespace convert
