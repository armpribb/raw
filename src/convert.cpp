#include "convert.h"

namespace convert {
bool engine::is_invalid() const {
  return !formatter || !input_adapter || !output_adapter;
}

bool engine::proceed() const {
  if (is_invalid()) {
    return false;
  }

  const auto raw_input = input_adapter->read();

  if (raw_input.empty()) {
    return false;
  }

  const auto formatted_output = formatter->process(raw_input);

  output_adapter->write(formatted_output);

  return true;
}

void engine::run() const {
  while (proceed())
    ;
}
} // namespace convert
