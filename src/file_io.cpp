#include "file_io.h"
#include "stream_wrap.h"

#include <nowide/fstream.hpp>

namespace fileio {

std::vector<uint8_t> read_file_as_binary(const std::string &filename) {
  nowide::ifstream input_file(filename, std::ios::binary);

  if (!input_file.is_open()) {
    return {};
  }

  input_file.unsetf(std::ios_base::skipws);

  std::vector<uint8_t> byte_vec{std::istream_iterator<uint8_t>(input_file),
                                std::istream_iterator<uint8_t>()};

  return byte_vec;
}

class fstream_provider_impl : public fstream_provider {
public:
  std::ostream *get_ostream(const std::string &filename) override;
  std::istream *get_istream(const std::string &filename) override;

private:
  std::map<std::string, std::ifstream> in_files;
  std::map<std::string, std::ofstream> out_files;
};

std::ostream *fstream_provider_impl::get_ostream(const std::string &filename) {
  if (filename.empty())
    return nullptr;

  auto [map_element, is_new] = out_files.try_emplace(filename);

  auto &file = map_element->second;

  if (is_new || !file.is_open())
    file.open(filename);

  if (file.is_open())
    return &file;

  return nullptr;
}

std::istream *fstream_provider_impl::get_istream(const std::string &filename) {
  if (filename.empty())
    return nullptr;

  auto [map_element, is_new] = in_files.try_emplace(filename);

  auto &file = map_element->second;

  if (is_new || !file.is_open())
    file.open(filename);

  if (file.is_open())
    return &file;

  return nullptr;
}

std::unique_ptr<fstream_provider> get_fstream_provider() {
  return std::make_unique<fstream_provider_impl>();
}

} // namespace fileio