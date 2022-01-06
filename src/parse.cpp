#include "parse.h"

#include <algorithm>
#include <cxxopts.hpp>
#include <memory>
#include <nowide/iostream.hpp>
#include <sstream>

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
    ("g,n-byte-group", "group n bytes together", cxxopts::value<uint8_t>()->default_value("1"))
    ("b,byte-separator", "choose byte separator", cxxopts::value<std::string>()->default_value(" "))
    ("h,help", "print help", cxxopts::value<bool>()->default_value("false"));
  // clang-format on
};

void engine::do_parse(int argc, char **argv) {
  try {
    result = options.parse(argc, argv);
    is_help_cmd = result["help"].as<bool>();
    valid_result = true;
  } catch (const cxxopts::OptionException &e) {
    queue_message(e.what());
  }
}

void engine::print_help() const { nowide::cout << options.help() << "\n"; }

bool engine::is_valid_non_help_cmd() const {
  return (valid_result && !is_help_cmd);
}

void engine::print_output() {
  auto print = [](const std::string &msg) { nowide::cout << msg << "\n"; };
  std::for_each(message_queue.cbegin(), message_queue.cend(), print);

  message_queue.clear();

  if (!is_valid_non_help_cmd()) {
    print_help();
  }
}

void engine::queue_message(const char *msg) {
  std::ostringstream oss;

  oss << msg << "\n";

  message_queue.emplace_back(oss.str());
}

std::unique_ptr<format::engine> engine::get_format() const {
  format::config config{};

  config.use_hex_prefix = result["use-hex-prefix"].as<bool>();
  config.use_uppercase = result["use-uppercase"].as<bool>();
  config.n_byte_group = result["n-byte-group"].as<uint8_t>();
  config.byte_separator = result["byte-separator"].as<std::string>();

  return std::make_unique<format::engine>(config);
}

std::unique_ptr<input::interface> engine::get_input() const {
  const auto value = result["input"].as<std::string>();

  if (value == "console") {
    return std::make_unique<input::from_console>();
  } else if (value == "file") {
    const auto &files = result["file"].as<std::vector<std::string>>();
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
