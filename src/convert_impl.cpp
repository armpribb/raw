#include "convert_impl.h"

#include <array>
#include <memory>
#include <sstream>
#include <utility>

namespace convert {

namespace detail {
constexpr std::array<char, 14> example{{"Hello, World!"}};

std::string get_example_format(format::interface &formatter,
                               const ios_abstract &ios) {
  const auto input_adapter = input::get_input_adapter(input_type::internal);

  (void)input::_internal_set(*input_adapter, example.data());
  const auto byte_vec = input_adapter->read(ios);
  const auto output_str = formatter.process(byte_vec);

  std::ostringstream oss{};
  oss << "format: " << output_str << " (\"" << example.data() << "\")";

  return oss.str();
}
} // namespace detail

engine::engine(std::unique_ptr<format::interface> fmt,
               std::unique_ptr<input::interface> in,
               std::unique_ptr<output::interface> out,
               std::unique_ptr<ios_abstract> ios)
    : formatter(std::move(fmt)), input_adapter(std::move(in)),
      output_adapter(std::move(out)), iostream(std::move(ios)) {}

bool engine::proceed() const {
  const auto raw_input = input_adapter->read(*iostream);

  if (raw_input.empty()) {
    return false;
  }

  const auto formatted_output = formatter->process(raw_input);

  output_adapter->write(formatted_output, iostream->cout);

  return true;
}

void engine::run() const {
  while (proceed())
    ;
}

std::unique_ptr<convert::interface>
get_converter(const parse_result &config, std::unique_ptr<ios_abstract> ios,
              print_func print) {
  auto fmt = format::get_format_engine(config.format);
  auto in = input::get_input_adapter(config.input, config.input_args());
  auto out = output::get_output_adapter(config.output);

  if (config.verbose) {
    const auto example = detail::get_example_format(*fmt, *ios);
    print(example);
    print(in->info());
    print(out->info());
  }

  return std::make_unique<convert::engine>(std::move(fmt), std::move(in),
                                           std::move(out), std::move(ios));
}

} // namespace convert
