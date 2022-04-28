#pragma once

#include <cxxopts.hpp>
#include <string>
#include <vector>

#include "types.h"

namespace parse {
class engine {
public:
  engine(PrintFunc _print = print_nothing);

  parse_result do_parse(int argc, char **argv);
  std::string get_help_msg() const;

private:
  cxxopts::Options cxx_options;
  PrintFunc print;
};
} // namespace parse
