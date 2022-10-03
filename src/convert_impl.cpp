#include "convert_impl.h"

#include <array>
#include <memory>
#include <sstream>
#include <utility>

namespace convert {

namespace detail {
std::string get_example_format(const format_config &config = {}) {
  constexpr auto example = "Hello, World!";
  const auto byte_vec = input::read(example);
  const auto result = format::process(byte_vec, config);

  return "format: " + result + " (\"" + example + "\")";
}
} // namespace detail

engine::engine(std::unique_ptr<format::interface> fmt,
               std::unique_ptr<input::interface> in,
               std::unique_ptr<output::interface> out, stream_provider &ios)
    : formatter(std::move(fmt)), input_adapter(std::move(in)),
      output_adapter(std::move(out)), iostream(ios) {}

bool engine::proceed() const {
  const auto raw_input = input_adapter->read(iostream);

  if (raw_input.empty()) {
    return false;
  }

  const auto formatted_output = formatter->process(raw_input);

  output_adapter->write(formatted_output, iostream);

  return true;
}

void engine::run() const {
  while (proceed())
    ;
}

std::unique_ptr<convert::interface> get_converter(const convert_config &config,
                                                  stream_provider &ios,
                                                  print_func print) {
  auto fmt = format::get_format_engine(config.format);
  auto in = input::get_input_adapter(config.input, config.input_args);
  auto out = output::get_output_adapter(config.output, config.set_result);

  if (config.verbose) {
    const auto example = detail::get_example_format(config.format);
    print(example);
    print(in->info());
    print(out->info());
  }

  return std::make_unique<convert::engine>(std::move(fmt), std::move(in),
                                           std::move(out), ios);
}

} // namespace convert
