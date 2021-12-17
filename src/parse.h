#pragma once

#include <cxxopts.hpp>
#include <memory>

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

namespace parse {
class engine {
public:
  engine();

  std::unique_ptr<format::engine> get_format() const;
  std::unique_ptr<input::interface> get_input() const;
  std::unique_ptr<output::interface> get_output() const;

  bool do_parse(int argc, char **argv);

private:
  cxxopts::Options options;
  cxxopts::ParseResult result;
};
} // namespace parse