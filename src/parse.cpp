#include "parse.h"

namespace parse {
namespace detail {
format_config get_format(const cxxopts::ParseResult &result) {
  format_config config{};

  config.use_hex_prefix = result["hex-prefix"].as<bool>();
  config.use_uppercase = result["uppercase"].as<bool>();
  config.n_byte_group = result["n-byte-group"].as<uint8_t>();
  config.byte_separator = result["group-separator"].as<std::string>();

  return config;
}

input_type get_input(const cxxopts::ParseResult &result) {
  const auto value = result["input"].as<std::string>();

  if (value == "console") {
    return input_type::console;
  } else if (value == "file") {
    return input_type::file;
  } else {
    return input_type::invalid;
  }
}

output_type get_output(const cxxopts::ParseResult &result) {
  const auto value = result["output"].as<std::string>();

  if (value == "clipboard") {
    return output_type::clipboard;
  } else if (value == "console") {
    return output_type::console;
  } else if (value == "file") {
    return output_type::file;
  } else {
    return output_type::invalid;
  }
}
} // namespace detail

engine::engine(print_func _print)
    : cxx_options(
          "raw",
          "get hex-code representation of any cleartext or binary input"),
      print(_print) {
  // clang-format off
  cxx_options.add_options()
    ("i,input", "choose input [console|file]", cxxopts::value<std::string>()->default_value("console"))
    ("o,output", "choose output [clipboard|console|file]", cxxopts::value<std::string>()->default_value("clipboard"))
    ("f,file", "specify file(s) to convert (multiple possible with additional flag each)", cxxopts::value<std::vector<std::string>>()->default_value(""))
    ("n,n-byte-group", "group n bytes together", cxxopts::value<uint8_t>()->default_value("1"))
    ("p,hex-prefix", "add '0x' prefix to hex values", cxxopts::value<bool>()->default_value("false"))
    ("s,group-separator", "choose byte group separator", cxxopts::value<std::string>()->default_value(" "))
    ("u,uppercase", "use uppercase hex values", cxxopts::value<bool>()->default_value("false"))
    ("v,verbose", "verbose output", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "print help", cxxopts::value<bool>()->default_value("false"));
  // clang-format on
};

parse_result engine::do_parse(int argc, char **argv) {
  cxxopts::ParseResult cxx_result{};

  try {
    cxx_result = cxx_options.parse(argc, argv);
  } catch (const cxxopts::OptionException &e) {
    print(e.what());
    print(get_help_msg());
    return {.is_help_cmd = true};
  }

  parse_result result{};

  result.is_help_cmd = cxx_result["help"].as<bool>();

  if (result.is_help_cmd) {
    print(get_help_msg());
    return result;
  }

  result.format = detail::get_format(cxx_result);
  result.input = detail::get_input(cxx_result);
  result.output = detail::get_output(cxx_result);
  result.verbose = cxx_result["verbose"].as<bool>();

  result.filenames = [files =
                          cxx_result["file"].as<std::vector<std::string>>()]() {
    return files;
  };

  return result;
}

std::string engine::get_help_msg() const { return cxx_options.help(); }
} // namespace parse
