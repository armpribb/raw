#pragma once

#include <cstdint>
#include <functional>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

using print_func = std::function<void(const std::string &)>;
using set_string_func = std::function<void(const std::string &)>;

inline void set_none(const std::string &) {}

enum class input_type : uint8_t {
  invalid = 0,
  console,
  file,
  string,
  internal
};

enum class output_type : uint8_t {
  invalid = 0,
  clipboard,
  console,
  file,
  string
};

struct format_config {
  bool use_hex_prefix{false};
  bool use_uppercase{false};
  uint8_t n_byte_group{1};
  std::string byte_separator{" "};
};

struct convert_config {
  format_config format;
  input_type input;
  output_type output;
  bool verbose;
  std::vector<std::string> input_args;
  set_string_func set_result;
};

struct stream_provider {
  stream_provider(std::ostream &cerr, std::istream &cin, std::ostream &cout)
      : err(cerr), in(cin), out(cout), secondary_out(cout) {}
  stream_provider(std::ostream &cerr, std::istream &cin, std::ostream &cout,
                  std::ostream &secondary_cout)
      : err(cerr), in(cin), out(cout), secondary_out(secondary_cout) {}
  std::ostream &err;
  std::istream &in;
  std::ostream &out;
  std::ostream &secondary_out;
};
