#include "stream_io.h"

#include <nowide/iostream.hpp>

namespace streamio {

provider get_provider(fileio::provider &fileio, const convert_config &config) {
  provider streamio{.err = &nowide::cerr};

  if (config.input == input_type::console &&
      config.output == output_type::console) {
    streamio.in = &nowide::cin;
    streamio.info = &nowide::cout;
    streamio.out = &nowide::cout;
  } else if (config.input == input_type::console &&
             config.output == output_type::clipboard) {
    streamio.in = &nowide::cin;
    streamio.info = &nowide::cout;
  } else if (config.input == input_type::console &&
             config.output == output_type::file) {
    streamio.in = &nowide::cin;
    streamio.info = &nowide::cout;
    streamio.out = fileio.get_ostream(config.out_file);
  } else if (config.input == input_type::file &&
             config.output == output_type::console) {
    streamio.in = fileio.get_istream(config.in_file);
    streamio.info = &nowide::cout;
    streamio.out = &nowide::cout;
  } else if (config.input == input_type::file &&
             config.output == output_type::clipboard) {
    streamio.in = fileio.get_istream(config.in_file);
    streamio.info = &nowide::cout;
    streamio.prompt = &nowide::cin;
  } else if (config.input == input_type::file &&
             config.output == output_type::file) {
    streamio.in = fileio.get_istream(config.in_file);
    streamio.info = &nowide::cout;
    streamio.out = fileio.get_ostream(config.out_file);
  } else if (config.input == input_type::file_batch &&
             config.output == output_type::console) {
    streamio.info = &nowide::cout;
    streamio.out = &nowide::cout;
  } else if (config.input == input_type::file_batch &&
             config.output == output_type::clipboard) {
    streamio.info = &nowide::cout;
    streamio.prompt = &nowide::cin;
  } else if (config.input == input_type::file_batch &&
             config.output == output_type::file) {
    streamio.out = fileio.get_ostream(config.out_file);
  }

  return streamio;
}

} // namespace streamio