#pragma once

#include "convert.h"

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

namespace convert {

class engine : public interface {
public:
  engine(std::unique_ptr<format::interface> fmt,
         std::unique_ptr<input::interface> in,
         std::unique_ptr<output::interface> out,
         std::unique_ptr<ios_abstract> ios);

  void run() const override;
  [[nodiscard]] bool proceed() const;

private:
  std::unique_ptr<format::interface> formatter;
  std::unique_ptr<input::interface> input_adapter;
  std::unique_ptr<output::interface> output_adapter;
  std::unique_ptr<ios_abstract> iostream;
};

} // namespace convert
