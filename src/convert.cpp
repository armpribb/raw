#include "convert.h"

#include <sstream>

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

namespace convert {
namespace detail {
std::string get_example_format(format::interface &formatter) {
  const char example[] = "Hello, World!";

  const auto input_adapter = input::get_input_adapter(input_type::internal);

  (void)input::_internal_set(*input_adapter, example);
  const auto byte_vec = input_adapter->read();
  const auto output_str = formatter.process(byte_vec);

  std::ostringstream oss{};
  oss << "format: " << output_str << " (\"" << example << "\")";

  return oss.str();
}
} // namespace detail

class engine : public interface {
public:
  engine(const parse_result &config, print_func _print = no_print);

  void run() const override;

private:
  bool is_invalid() const;
  bool proceed() const;

  std::unique_ptr<format::interface> formatter;
  std::unique_ptr<input::interface> input_adapter;
  std::unique_ptr<output::interface> output_adapter;

  print_func print;
};

engine::engine(const parse_result &config, print_func _print)
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

std::unique_ptr<convert::interface> get_converter(const parse_result &config,
                                                  print_func _print) {
  return std::make_unique<convert::engine>(config, _print);
}

} // namespace convert
