#include "parse.h"

#include <cxxopts.hpp>
#include <memory>
#include <nowide/iostream.hpp>

#include "input_adapter.h"
#include "output_adapter.h"

namespace parse {
engine::engine()
    : options("raw", "convert any input to hex-encoded binary output") {
  // clang-format off
  options.add_options()
    ("i,input", "choose input", cxxopts::value<std::string>()->default_value("console"))
    ("o,output", "choose output", cxxopts::value<std::string>()->default_value("clipboard"))
    ("f,file", "specify file to convert", cxxopts::value<std::vector<std::string>>())
    ("p,use-hex-prefix", "add '0x' prefix to hex values", cxxopts::value<bool>()->default_value("false"))
    ("u,use-uppercase", "convert hex values to uppercase", cxxopts::value<bool>()->default_value("false"))
    ("b,byte-separator", "choose byte separator", cxxopts::value<std::string>()->default_value(" "));
  // clang-format on
};

bool engine::do_parse(int argc, char **argv) {
  try {
    result = options.parse(argc, argv);
  } catch (cxxopts::OptionException &e) {
    nowide::cerr << e.what() << "\n\nHelp:\n" << options.help() << "\n";
    return false;
  }

  return true;
}

std::unique_ptr<format::engine> engine::get_format() const {
  format::config config{};

  config.use_hex_prefix = result["use-hex-prefix"].as<bool>();
  config.use_uppercase = result["use-uppercase"].as<bool>();
  config.byte_separator = result["byte-separator"].as<std::string>();

  return std::make_unique<format::engine>(config);
}

std::unique_ptr<input::interface> engine::get_input() const {
  const auto value = result["input"].as<std::string>();

  if (value == "console") {
    return std::make_unique<input::from_console>();
  } else if (value == "file") {
    const auto files = result["file"].as<std::vector<std::string>>();
    return std::make_unique<input::from_file>(files);
  } else {
    return std::make_unique<input::invalid>();
  }
}

std::unique_ptr<output::interface> engine::get_output() const {
  const auto value = result["output"].as<std::string>();

  if (value == "clipboard") {
    return std::make_unique<output::to_clipboard>();
  } else if (value == "console") {
    return std::make_unique<output::to_console>();
  } else if (value == "file") {
    return std::make_unique<output::to_file>();
  } else {
    return std::make_unique<output::invalid>();
  }
}
} // namespace parse