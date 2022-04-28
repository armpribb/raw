#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

using PrintFunc = std::function<void(const std::string &)>;
using GetStringVectorFunc = std::function<std::vector<std::string>(void)>;

inline void print_nothing(const std::string &) {}
inline std::vector<std::string> none() { return {}; }

enum class input_type : uint8_t { invalid = 0, console, file };

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
  GetStringVectorFunc filenames{none};
};
