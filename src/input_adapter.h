#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace input {

class interface {
public:
  interface() = default;
  virtual ~interface() = default;
  [[nodiscard]] virtual const char *info() const = 0;
  [[nodiscard]] virtual std::vector<uint8_t>
  read(const ios_abstract &ios) const = 0;

protected:
  interface(const interface &) = default;
  interface(interface &&) = default;
  interface &operator=(const interface &) = default;
  interface &operator=(interface &&) = default;
};

std::unique_ptr<input::interface>
get_input_adapter(input_type type, const std::vector<std::string> &input = {});

bool _internal_set(input::interface &instance, const char *c_str);

} // namespace input
