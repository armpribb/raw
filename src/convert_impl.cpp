#include "convert_impl.h"
#include "format.h"
#include "input.h"
#include "output.h"
#include "stream_io.h"
#include "types.h"

namespace convert {

namespace detail {
std::string get_example_output(const format_config &config) {
  constexpr auto example_str = "Hello, World!";
  auto raw_data = input::read(example_str);
  if (config.use_little_endian)
    std::reverse(raw_data.begin(), raw_data.end());
  return format::process(raw_data, config);
}

void print_verbose_info(streamio::outstream info,
                        const convert_config &config) {
  info << get_example_output(config.format) << "\n";
}

void write_to_output(const streamio::provider &ios, const std::string &str,
                     bool use_clipbard) {
  if (use_clipbard) {
    output::write_to_clipboard(str, ios);
    return;
  }
  output::write_to_stream(str, ios);
}
} // namespace detail

engine::engine(convert_config config_)
    : m_fileio(fileio::get_provider()), m_config(std::move(config_)),
      m_streamio(streamio::get_provider(*m_fileio, m_config)) {}

void engine::run() const {
  if (m_config.verbose) {
    detail::print_verbose_info(m_streamio.info, m_config);
  }

  if (m_config.input == input_type::file_batch) {
    run_file_batch();
    return;
  }

  while (proceed(m_config.format))
    ;
}

void engine::run_file_batch() const {
  const auto &filenames = m_config.in_args;
  for (auto &filename : filenames) {
    auto raw_data = fileio::read_file_as_binary(filename);
    auto formatted_string = format::process(raw_data, m_config.format);
    m_streamio.info << "<" << filename << ">\n";
    detail::write_to_output(m_streamio, formatted_string,
                            m_config.output == output_type::clipboard);
  }
}

bool engine::proceed(const format_config &format) const {
  if (m_streamio.prompt.get() == nullptr)
    m_streamio.info << "> ";

  auto raw_data = input::read(m_streamio.in);

  if (raw_data.empty())
    return false;

  if (m_config.format.use_little_endian)
    std::reverse(raw_data.begin(), raw_data.end());

  const auto formatted_string = format::process(raw_data, format);
  detail::write_to_output(m_streamio, formatted_string,
                          m_config.output == output_type::clipboard);

  return true;
}

std::unique_ptr<convert::interface>
get_converter(const convert_config &config) {
  return std::make_unique<convert::engine>(config);
}

} // namespace convert