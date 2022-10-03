#pragma once

#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace format {

std::string process(const std::vector<uint8_t> &raw_data,
                    const format_config &config = {});

class interface {
public:
  interface() = default;
  virtual ~interface() = default;
  [[nodiscard]] virtual std::string
  process(const std::vector<uint8_t> &raw_data) const = 0;

protected:
  interface(const interface &) = default;
  interface(interface &&) = default;
  interface &operator=(const interface &) = default;
  interface &operator=(interface &&) = default;
};

std::unique_ptr<format::interface>
get_format_engine(const format_config &config = {});

} // namespace format
