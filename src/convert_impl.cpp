#include "convert_impl.h"

#include "config.h"
#include "format.h"
#include "input.h"
#include "output.h"
#include "stream_io.h"
#include "types.h"

namespace convert {

namespace detail {
std::string get_example_output(const format_config &config) {
  constexpr auto example_str = "Hello, World!";
  auto raw_data = input::read_string(example_str, config.use_little_endian);
  return format::process(raw_data, config);
}

void print_verbose_info(const streamio::outstream &info,
                        const convert_config &config) {
  info << get_example_output(config.format) << "\n";
}

std::vector<uint8_t> read_from_input(const streamio::provider &ios,
                                     const format_config &config,
                                     input_type intype) {
  std::vector<uint8_t> raw_data{};

  switch (intype) {
  case input_type::file_batch:
    break;
  case input_type::console:
    ios.info << "> ";
  default:
    raw_data = input::read_stream(ios.in.get(), config.use_little_endian);
    break;
  }

  return raw_data;
}

void write_to_output(const streamio::provider &ios, const std::string &str,
                     output_type outtype) {
  switch (outtype) {
  case output_type::clipboard:
    output::write_to_clipboard(str, ios);
    break;
  default:
    output::write_to_stream(str, ios);
    break;
  }
}

std::string process_file(const std::string &filename,
                         const format_config &config,
                         streamio::outstream err = nullptr) {
  auto raw_data = fileio::read_file_as_binary(filename, err);
  if (config.use_little_endian) {
    std::reverse(raw_data.begin(), raw_data.end());
  }
  return format::process(raw_data, config);
}
} // namespace detail

void convert_file_batch(const streamio::provider &ios,
                        const std::vector<std::string> &filenames,
                        const format_config &config, output_type outtype) {
  for (auto &filename : filenames) {
    ios.info << "<file: " << filename << ">\n";
    auto formatted_string = detail::process_file(filename, config, ios.err);
    detail::write_to_output(ios, formatted_string, outtype);
  }
}

bool convert_next(const streamio::provider &ios, const format_config &config,
                  input_type intype, output_type outtype) {
  const auto raw_data = detail::read_from_input(ios, config, intype);

  if (raw_data.empty())
    return false;

  const auto formatted_string = format::process(raw_data, config);
  detail::write_to_output(ios, formatted_string, outtype);

  return true;
}

engine::engine(convert_config config_)
    : m_fileio(fileio::get_provider()), m_config(std::move(config_)),
      m_streamio(config::get_stream_provider(*m_fileio, m_config)) {}

void engine::run() const {
  if (m_config.verbose) {
    detail::print_verbose_info(m_streamio.info, m_config);
  }

  if (m_config.input == input_type::file_batch) {
    convert_file_batch(m_streamio, m_config.in_args, m_config.format,
                       m_config.output);
  } else {
    run_loop();
  }
}

void engine::run_loop() const {
  while (convert_next(m_streamio, m_config.format, m_config.input,
                      m_config.output))
    ;
}

std::unique_ptr<convert::interface>
get_converter(const convert_config &config) {
  return std::make_unique<convert::engine>(config);
}

} // namespace convert