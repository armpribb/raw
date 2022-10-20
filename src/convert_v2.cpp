#include "convert_v2.h"
#include "format.h"
#include "input.h"
#include "output.h"

namespace convert {

engine_v2::engine_v2(convert_config_v2 config_)
    : fileio(fileio::get_fstream_provider()), config(std::move(config_)),
      iostream(streamio::get_stream_provider(*fileio, config)) {}

void engine_v2::run() const {
  if (config.input == input_type::file_batch) {
    run_file_batch();
    return;
  }

  while (proceed(config.format))
    ;
}

void engine_v2::run_file_batch() const {
  const auto &filenames = config.in_args;
  for (auto &filename : filenames) {
    auto raw_data = fileio::read_file_as_binary(filename);
    auto formatted_string = format::process(raw_data, config.format);
    iostream.info << "<" << filename << ">\n";
    write(formatted_string);
  }
}

bool engine_v2::proceed(const format_config &format) const {
  if (iostream.prompt.get() == nullptr)
    iostream.info << "> ";

  auto raw_data = input::read(iostream.in);

  if (raw_data.empty())
    return false;

  if (config.format.use_little_endian)
    std::reverse(raw_data.begin(), raw_data.end());

  const auto formatted_string = format::process(raw_data, format);
  write(formatted_string);

  return true;
}

void engine_v2::write(const std::string &str) const {
  if (config.output == output_type::clipboard) {
    output::write_to_clipboard(str, iostream);
    return;
  }

  output::write_to_stream(str, iostream);
}

std::unique_ptr<convert::interface>
get_converter_v2(const convert_config_v2 &config) {
  return std::make_unique<convert::engine_v2>(config);
}

} // namespace convert