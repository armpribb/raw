#pragma once

#include <memory>
#include <string>

#include "types.h"

namespace output {

class interface {
public:
  interface() = default;
  virtual ~interface() = default;
  [[nodiscard]] virtual const char *info() const = 0;
  virtual void write(const std::string &str, std::ostream &cout) const = 0;

protected:
  interface(const interface &) = default;
  interface(interface &&) = default;
  interface &operator=(const interface &) = default;
  interface &operator=(interface &&) = default;
};

std::unique_ptr<output::interface> get_output_adapter(output_type type);

} // namespace output
