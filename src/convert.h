#pragma once

#include <memory>

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"
#include "types.h"

namespace convert {
class engine {
public:
  engine(const parse_result &config, print_func _print = no_print);

  void run() const;

private:
  bool is_invalid() const;
  bool proceed() const;

  std::unique_ptr<format::engine> formatter;
  std::unique_ptr<input::interface> input_adapter;
  std::unique_ptr<output::interface> output_adapter;

  print_func print;
};
} // namespace convert
