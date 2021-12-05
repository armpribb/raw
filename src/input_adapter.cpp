#include "input_adapter.h"

#include <nowide/fstream.hpp>
#include <nowide/iostream.hpp>
#include <stdexcept>
#include <string>

namespace input {
namespace detail {
void read_file_as_binary(std::vector<uint8_t> &byte_vec,
                         const std::string &filename) {
  nowide::ifstream inputfile(filename, std::ios::binary);

  if (!inputfile.is_open()) {
    nowide::cerr << "Failed to open '" << filename << "'\n";
    return;
  }

  inputfile.unsetf(std::ios_base::skipws);

  std::streampos inputfile_size;

  inputfile.seekg(0, std::ios::end);
  inputfile_size = inputfile.tellg();
  inputfile.seekg(0, std::ios::beg);

  byte_vec.reserve(inputfile_size);

  byte_vec.insert(byte_vec.begin(), std::istream_iterator<uint8_t>(inputfile),
                  std::istream_iterator<uint8_t>());
}
} // namespace detail

std::vector<uint8_t> from_console::read() const {
  std::vector<uint8_t> output_vec{};

  std::string input_str;

  std::getline(nowide::cin, input_str);

  if (input_str.back() == '\r') {
    input_str.pop_back();
  }

  if (!input_str.empty()) {
    for (const auto &c : input_str) {
      output_vec.push_back(static_cast<uint8_t>(c));
    }
  }

  return output_vec;
};

std::string from_file::get_next_filename() const {
  try {
    const auto &next = filenames.at(index);
    ++index;
    return next;
  } catch (std::out_of_range &) {
  }

  return {};
}

std::vector<uint8_t> from_file::read() const {
  std::vector<uint8_t> output_vec{};

  const auto filename = get_next_filename();
  if (!filename.empty()) {
    detail::read_file_as_binary(output_vec, filename);
  }

  return output_vec;
};
} // namespace input