#include "convert_v2.h"
#include "file_io.h"
#include "format.h"
#include "input.h"
#include "output.h"
#include "types.h"

#include <algorithm>
#include <nowide/iostream.hpp>

namespace convert {

engine_v2::engine_v2(convert_config_v2 config_)
    : file(fileio::get_fstream_provider()), config(std::move(config_)),
      iostream({.err = &nowide::cerr}) {
  determine_in_stream();
  determine_out_stream();
}

void engine_v2::determine_in_stream() {
  switch (config.input) {
  case input_type::console:
    iostream.in = &nowide::cin;
    iostream.info = &nowide::cout;
    break;
  case input_type::file:
    iostream.in = file->get_istream(config.in_file);
    break;
  default:
    break;
  }
}

void engine_v2::determine_out_stream() {
  switch (config.output) {
  case output_type::console:
    iostream.out = &nowide::cout;
    break;
  case output_type::file:
    iostream.out = file->get_ostream(config.out_file);
    break;
  default:
    break;
  }
}

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
  std::for_each(filenames.begin(), filenames.end(),
                [this, &format = config.format](const std::string &filename) {
                  const auto raw_data = fileio::read_file_as_binary(filename);
                  const auto formatted_string =
                      format::process(raw_data, format);
                  iostream.out << "<" << filename << ">\n";
                  write(formatted_string);
                });
}

bool engine_v2::proceed(const format_config &format) const {
  const auto raw_data = input::read(iostream);

  if (raw_data.empty())
    return false;

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