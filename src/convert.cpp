#include "convert.h"

#include <array>
#include <sstream>
#include <utility>

#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

namespace convert {

namespace detail {
constexpr std::array<char, 14> example{{"Hello, World!"}};

template <size_t Size>
std::string array_to_string(const std::array<char, Size> &char_array) {
  return {char_array.begin(), char_array.end()};
}

std::string get_example_format(format::interface &formatter) {
  const auto input_adapter = input::get_input_adapter(input_type::internal);

  (void)input::_internal_set(*input_adapter, example.data());
  const auto byte_vec = input_adapter->read();
  const auto output_str = formatter.process(byte_vec);

  std::ostringstream oss{};
  oss << "format: " << output_str << " (\"" << array_to_string(example)
      << "\")";

  return oss.str();
}
} // namespace detail

class engine : public interface {
public:
  engine(const parse_result &config, queue_func _queue);

  void run() const override;

private:
  bool proceed() const;

  std::unique_ptr<format::interface> formatter;
  std::unique_ptr<input::interface> input_adapter;
  std::unique_ptr<output::interface> output_adapter;

  queue_func queue;
};

engine::engine(const parse_result &config, queue_func _queue)
    : formatter(format::get_format_engine(config.format)),
      input_adapter(
          input::get_input_adapter(config.input, config.str_input_args())),
      output_adapter(output::get_output_adapter(config.output)),
      queue(std::move(_queue)) {

  if (config.verbose) {
    const auto example = detail::get_example_format(*formatter);
    queue(example);
    queue(input_adapter->info());
    queue(output_adapter->info());
  }
}

bool engine::proceed() const {
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
                                                  queue_func _queue) {
  return std::make_unique<convert::engine>(config, _queue);
}

} // namespace convert
