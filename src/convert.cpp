#include "convert.h"

#include <sstream>

namespace convert {
namespace detail {
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

engine::engine(const parse_result &config, PrintFunc _print)
    : formatter(format::get_format_engine(config.format)),
      input_adapter(input::get_input_adapter(config.input, config.filenames())),
      output_adapter(output::get_output_adapter(config.output)), print(_print) {

  if (config.verbose) {
    const auto example = detail::get_example_format(*formatter);
    print(example);
    print(input_adapter->info());
    print(output_adapter->info());
  }
}

bool engine::is_invalid() const {
  return !formatter || !input_adapter || !output_adapter;
}

bool engine::proceed() const {
  if (is_invalid()) {
    return false;
  }

  const auto raw_input = input_adapter->read();

  if (raw_input.empty()) {
    return false;
  }

  const auto formatted_output = formatter->process(raw_input);

  output_adapter->write(formatted_output);

  return true;
}

void engine::run() const {
  while (proceed())
    ;
}
} // namespace convert
