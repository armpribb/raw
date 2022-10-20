#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

using print_func = std::function<void(const std::string &)>;
using set_string_func = std::function<void(const std::string &)>;

inline void set_none(const std::string &) {}

enum class input_type : uint8_t {
  invalid = 0,
  console,
  file,
  file_batch,
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
  bool use_little_endian{false};
  bool use_uppercase{false};
  uint8_t n_byte_group{1};
  std::string byte_separator{" "};
};

struct convert_config {
  format_config format;
  input_type input;
  output_type output;
  bool verbose;
  std::string in_file;
  std::string out_file;
  std::vector<std::string> in_args;
};
