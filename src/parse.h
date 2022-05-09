#pragma once

#include <cxxopts.hpp>
#include <string>
#include <vector>

#include "types.h"

namespace parse {
class engine {
public:
  engine(print_func _print = no_print);

  parse_result do_parse(int argc, char **argv);
  std::string get_help_msg() const;

private:
  cxxopts::Options cxx_options;
  print_func print;
};
} // namespace parse
