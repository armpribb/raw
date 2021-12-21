#pragma once

#include <cxxopts.hpp>
#include <memory>
#include <string>
#include <vector>

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

  void do_parse(int argc, char **argv);
  void print_output();
  bool is_valid_non_help_cmd() const;

private:
  void print_help() const;
  void queue_message(const char *msg);

  cxxopts::Options options;
  cxxopts::ParseResult result;

  bool is_help_cmd = false;
  bool valid_result = false;

  std::vector<std::string> message_queue{};
};
} // namespace parse
