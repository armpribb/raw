#include "stream_io.h"

#include <nowide/iostream.hpp>

namespace streamio {

provider get_stream_provider(fileio::provider &fileio,
                             const convert_config_v2 &config) {
  provider iostream{.err = &nowide::cerr};

  if (config.input == input_type::console &&
      config.output == output_type::console) {
    iostream.in = &nowide::cin;
    iostream.info = &nowide::cout;
    iostream.out = &nowide::cout;
  } else if (config.input == input_type::console &&
             config.output == output_type::clipboard) {
    iostream.in = &nowide::cin;
    iostream.info = &nowide::cout;
  } else if (config.input == input_type::console &&
             config.output == output_type::file) {
    iostream.in = &nowide::cin;
    iostream.info = &nowide::cout;
    iostream.out = fileio.get_ostream(config.out_file);
  } else if (config.input == input_type::file &&
             config.output == output_type::console) {
    iostream.in = fileio.get_istream(config.in_file);
    iostream.info = &nowide::cout;
    iostream.out = &nowide::cout;
  } else if (config.input == input_type::file &&
             config.output == output_type::clipboard) {
    iostream.in = fileio.get_istream(config.in_file);
    iostream.info = &nowide::cout;
    iostream.prompt = &nowide::cin;
  } else if (config.input == input_type::file &&
             config.output == output_type::file) {
    iostream.in = fileio.get_istream(config.in_file);
    iostream.info = &nowide::cout;
    iostream.out = fileio.get_ostream(config.out_file);
  } else if (config.input == input_type::file_batch &&
             config.output == output_type::console) {
    iostream.info = &nowide::cout;
    iostream.out = &nowide::cout;
  } else if (config.input == input_type::file_batch &&
             config.output == output_type::clipboard) {
    iostream.info = &nowide::cout;
    iostream.prompt = &nowide::cin;
  } else if (config.input == input_type::file_batch &&
             config.output == output_type::file) {
    iostream.out = fileio.get_ostream(config.out_file);
  }

  return iostream;
}
} // namespace streamio