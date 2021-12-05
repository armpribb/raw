#include "converter.h"

bool converter::proceed() const {
  const auto raw_input = input_adapter.read();

  if (raw_input.empty()) {
    return false;
  }

  const auto formatted_output = formatter.process(raw_input);

  output_adapter.write(formatted_output);

  return true;
}