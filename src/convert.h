#pragma once

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

namespace convert {
class engine {
public:
  engine(std::unique_ptr<format::engine> format,
         std::unique_ptr<input::interface> input,
         std::unique_ptr<output::interface> output)
      : input_adapter(std::move(input)), formatter(std::move(format)),
        output_adapter(std::move(output)){};

  void run() const;

private:
  bool is_invalid() const;
  bool proceed() const;

  std::unique_ptr<input::interface> input_adapter;
  std::unique_ptr<format::engine> formatter;
  std::unique_ptr<output::interface> output_adapter;
};
} // namespace convert
