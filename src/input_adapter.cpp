#include "input_adapter.h"

#include <iterator>
#include <nowide/fstream.hpp>
#include <nowide/iostream.hpp>
#include <stdexcept>

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

std::vector<uint8_t> string_to_byte_vector(const std::string &str) {
  std::vector<uint8_t> byte_buffer{};

  if (!str.empty()) {
    for (const auto &c : str) {
      byte_buffer.push_back(static_cast<uint8_t>(c));
    }
  }

  return byte_buffer;
}
} // namespace detail

std::vector<uint8_t> from_console::read() const {
  std::string input_str{};

  nowide::cout << "> ";
  std::getline(nowide::cin, input_str);

  return detail::string_to_byte_vector(input_str);
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

std::vector<uint8_t> from_internal::read() const {
  return detail::string_to_byte_vector(line);
}

void from_internal::set(const char *c_str) { line = c_str; }
} // namespace input
