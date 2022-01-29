#include "parse.h"

#include <algorithm>
#include <memory>
#include <nowide/iostream.hpp>
#include <sstream>

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

namespace parse {
namespace detail {
std::unique_ptr<format::engine> get_format(const cxxopts::ParseResult &result) {
  format::config config{};

  config.use_hex_prefix = result["hex-prefix"].as<bool>();
  config.use_uppercase = result["uppercase"].as<bool>();
  config.n_byte_group = result["n-byte-group"].as<uint8_t>();
  config.byte_separator = result["group-separator"].as<std::string>();

  return std::make_unique<format::engine>(config);
}

std::unique_ptr<input::interface>
get_input(const cxxopts::ParseResult &result) {
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

std::unique_ptr<output::interface>
get_output(const cxxopts::ParseResult &result) {
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

std::string get_example_format(format::engine &formatter) {
  const char example[] = "Hello, World!";

  input::from_internal input_adapter{};

  input_adapter.set(example);
  const auto byte_vec = input_adapter.read();
  const auto output_str = formatter.process(byte_vec);

  std::ostringstream oss{};
  oss << "format: " << output_str << " (\"" << example << "\")";

  return oss.str();
}
} // namespace detail

engine::engine()
    : options("raw", "get hex-code representation of any cleartext or binary input") {
  // clang-format off
  options.add_options()
    ("i,input", "choose input [console|file]", cxxopts::value<std::string>()->default_value("console"))
    ("o,output", "choose output [clipboard|console|file]", cxxopts::value<std::string>()->default_value("clipboard"))
    ("f,file", "specify file(s) to convert (multiple possible with additional flag each)", cxxopts::value<std::vector<std::string>>())
    ("n,n-byte-group", "group n bytes together", cxxopts::value<uint8_t>()->default_value("1"))
    ("p,hex-prefix", "add '0x' prefix to hex values", cxxopts::value<bool>()->default_value("false"))
    ("s,group-separator", "choose byte group separator", cxxopts::value<std::string>()->default_value(" "))
    ("u,uppercase", "use uppercase hex values", cxxopts::value<bool>()->default_value("false"))
    ("v,verbose", "verbose output", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "print help", cxxopts::value<bool>()->default_value("false"));
  // clang-format on
};

convert::engine engine::get_converter() {
  if (is_help_cmd) {
    return {nullptr, nullptr, nullptr};
  }

  auto format = detail::get_format(result);
  auto in = detail::get_input(result);
  auto out = detail::get_output(result);

  if (verbose) {
    const auto example = detail::get_example_format(*format);
    queue_message(example.c_str());
    queue_message(in->info());
    queue_message(out->info());
  }

  return {std::move(format), std::move(in), std::move(out)};
}

void engine::do_parse(int argc, char **argv) {
  try {
    result = options.parse(argc, argv);
    verbose = result["verbose"].as<bool>();
    is_help_cmd = result["help"].as<bool>();
  } catch (const cxxopts::OptionException &e) {
    queue_message(e.what());
  }
}

void engine::print_help() const { nowide::cout << options.help() << "\n"; }

void engine::print_output() {
  auto print = [](const std::string &msg) { nowide::cout << msg; };

  std::for_each(message_queue.cbegin(), message_queue.cend(), print);

  message_queue.clear();

  if (is_help_cmd) {
    print_help();
  }
}

void engine::queue_message(const char *msg) {
  std::ostringstream oss;

  oss << msg << "\n";

  message_queue.emplace_back(oss.str());
}
} // namespace parse
