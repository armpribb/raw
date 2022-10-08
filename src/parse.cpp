#include "parse.h"

#include <cxxopts.hpp>
#include <nowide/args.hpp>
#include <utility>

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
  } else if (value == "filebatch") {
    return input_type::file_batch;
  } else if (value == "string") {
    return input_type::string;
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

class engine : public interface {
public:
  explicit engine(print_func _print);

  convert_config do_parse(int argc, char **argv) override;
  convert_config_v2 do_parse_v2(int argc, char **argv) override;

private:
  cxxopts::Options cxx_options;
  print_func print;
};

engine::engine(print_func print_)
    : cxx_options(
          "raw",
          "get hex-code representation of any cleartext or binary input"),
      print(std::move(print_)) {
  // clang-format off
  cxx_options.add_options()
    ("i,input", "choose input [console|file|string]", cxxopts::value<std::string>()->default_value("console"))
    ("o,output", "choose output [clipboard|console|file]", cxxopts::value<std::string>()->default_value("clipboard"))
    ("a,args", "specify text string(s) or file(s) to convert, depending on input mode", cxxopts::value<std::vector<std::string>>()->default_value(""))
    ("r,infile", "specify input file (optional)", cxxopts::value<std::string>()->default_value(""))
    ("w,outfile", "specify output file (optional)", cxxopts::value<std::string>()->default_value(""))
    ("n,n-byte-group", "group n bytes together", cxxopts::value<uint8_t>()->default_value("1"))
    ("p,hex-prefix", "add '0x' prefix to hex values", cxxopts::value<bool>()->default_value("false"))
    ("s,group-separator", "choose byte group separator", cxxopts::value<std::string>()->default_value(" "))
    ("u,uppercase", "use uppercase hex values", cxxopts::value<bool>()->default_value("false"))
    ("v,verbose", "verbose output", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "print help", cxxopts::value<bool>()->default_value("false"));
  // clang-format on
};

convert_config engine::do_parse(int argc, char **argv) {
  nowide::args _(argc, argv);

  cxxopts::ParseResult cxx_result{};

  try {
    cxx_result = cxx_options.parse(argc, argv);
  } catch (const cxxopts::OptionException &e) {
    print(e.what());
    print(cxx_options.help());
    return {};
  }

  convert_config result{};

  auto is_help_cmd = cxx_result["help"].as<bool>();

  if (is_help_cmd) {
    print(cxx_options.help());
    return result;
  }

  result.format = detail::get_format(cxx_result);
  result.input = detail::get_input(cxx_result);
  result.output = detail::get_output(cxx_result);
  result.verbose = cxx_result["verbose"].as<bool>();

  result.input_args = cxx_result["args"].as<std::vector<std::string>>();

  return result;
}

convert_config_v2 engine::do_parse_v2(int argc, char **argv) {
  nowide::args _(argc, argv);

  cxxopts::ParseResult cxx_result{};

  try {
    cxx_result = cxx_options.parse(argc, argv);
  } catch (const cxxopts::OptionException &e) {
    print(e.what());
    print(cxx_options.help());
    return {};
  }

  convert_config_v2 result{};

  auto is_help_cmd = cxx_result["help"].as<bool>();

  if (is_help_cmd) {
    print(cxx_options.help());
    return result;
  }

  result.format = detail::get_format(cxx_result);
  result.input = detail::get_input(cxx_result);
  result.output = detail::get_output(cxx_result);
  // result.verbose = cxx_result["verbose"].as<bool>();
  result.in_file = cxx_result["infile"].as<std::string>();
  result.out_file = cxx_result["outfile"].as<std::string>();
  result.in_args = cxx_result["args"].as<std::vector<std::string>>();

  return result;
}

std::unique_ptr<parse::interface> get_parser(const print_func &print) {
  return std::make_unique<parse::engine>(print);
}

} // namespace parse
