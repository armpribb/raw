#pragma once

#include <cstdint>
#include <functional>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

using print_func = std::function<void(const std::string &)>;
using get_string_vector_func = std::function<std::vector<std::string>(void)>;

inline void _none(const std::string &) {}
inline std::vector<std::string> _nothing() { return {}; }

enum class input_type : uint8_t {
  invalid = 0,
  console,
  file,
  string,
  internal
};

enum class output_type : uint8_t { invalid = 0, clipboard, console, file };

struct format_config {
  bool use_hex_prefix{false};
  bool use_uppercase{false};
  uint8_t n_byte_group{1};
  std::string byte_separator{" "};
};

struct parse_result {
  format_config format;
  input_type input;
  output_type output;
  bool is_help_cmd;
  bool verbose;
  get_string_vector_func input_args{_nothing};
};

struct ios_abstract {
  ios_abstract(std::ostream &_cerr, std::istream &_cin, std::ostream &_cout)
      : cerr(_cerr), cin(_cin), cout(_cout) {}
  std::ostream &cerr;
  std::istream &cin;
  std::ostream &cout;
};
