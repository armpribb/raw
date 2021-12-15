#pragma once

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

class converter {
public:
  converter(input::interface &input, format::engine &format,
            output::interface &output)
      : input_adapter(input), formatter(format), output_adapter(output){};

  bool proceed() const;

private:
  input::interface &input_adapter;
  format::engine &formatter;
  output::interface &output_adapter;
};
