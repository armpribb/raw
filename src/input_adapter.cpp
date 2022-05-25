#include "input_adapter.h"

#include <iterator>
#include <memory>
#include <nowide/fstream.hpp>
#include <nowide/iostream.hpp>
#include <stdexcept>
#include <typeinfo>

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

class from_console : public interface {
public:
  const char *info() const override { return "input: console"; }
  std::vector<uint8_t> read() const override {
    std::string input_str{};

    nowide::cout << "> ";
    std::getline(nowide::cin, input_str);

    return detail::string_to_byte_vector(input_str);
  }
};

class from_file : public interface {
public:
  from_file(const std::vector<std::string> &names) : filenames(names){};
  const char *info() const override { return "input: file"; }
  std::vector<uint8_t> read() const override {
    std::vector<uint8_t> output_vec{};

    const auto filename = get_next_filename();
    if (!filename.empty()) {
      detail::read_file_as_binary(output_vec, filename);
    }

    return output_vec;
  }

private:
  std::string get_next_filename() const {
    try {
      const auto &next = filenames.at(index);
      ++index;
      return next;
    } catch (std::out_of_range &) {
    }

    return {};
  }

  std::vector<std::string> filenames;
  mutable size_t index = 0;
};

class from_string : public interface {
public:
  from_string(const std::vector<std::string> &_input) : input(_input) {}
  const char *info() const override { return "input: text"; }
  std::vector<uint8_t> read() const override {
    std::vector<uint8_t> output_vec{};

    const auto str = get_next_string();
    if (!str.empty()) {
      output_vec = detail::string_to_byte_vector(str);
    }

    return output_vec;
  }

private:
  std::string get_next_string() const {
    try {
      const auto &next = input.at(index);
      ++index;
      return next;
    } catch (std::out_of_range &) {
    }

    return {};
  }

  std::vector<std::string> input;
  mutable size_t index = 0;
};

class from_internal : public interface {
public:
  const char *info() const override { return "input: internal"; }
  std::vector<uint8_t> read() const override {
    return detail::string_to_byte_vector(line);
  }
  void set(const char *c_str) { line = c_str; }

private:
  std::string line{};
};

class invalid : public interface {
public:
  const char *info() const override { return "input: invalid"; }
  std::vector<uint8_t> read() const override { return {}; }
};

std::unique_ptr<input::interface>
get_input_adapter(input_type type, const std::vector<std::string> &input) {
  switch (type) {
  case input_type::console:
    return std::make_unique<input::from_console>();
  case input_type::file:
    return std::make_unique<input::from_file>(input);
  case input_type::string:
    return std::make_unique<input::from_string>(input);
  case input_type::internal:
    return std::make_unique<input::from_internal>();
  default:
    return std::make_unique<input::invalid>();
  }
}

bool _internal_set(input::interface &instance, const char *c_str) {
  try {
    auto &internal = dynamic_cast<input::from_internal &>(instance);
    internal.set(c_str);
  } catch (std::bad_cast &) {
    return false;
  }
  return true;
}

} // namespace input
