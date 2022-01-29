#pragma once

#include <cxxopts.hpp>
#include <string>
#include <vector>

#include "convert.h"

namespace parse {
class engine {
public:
  engine();

  convert::engine get_converter();

  void do_parse(int argc, char **argv);
  void print_output();

private:
  void print_help() const;
  void queue_message(const char *msg);

  cxxopts::Options options;
  cxxopts::ParseResult result;

  bool is_help_cmd = true;
  bool verbose = false;

  std::vector<std::string> message_queue{};
};
} // namespace parse
