#include "input_adapter.h"

#include <iterator>
#include <memory>
#include <nowide/fstream.hpp>
#include <stdexcept>
#include <utility>

namespace input {

namespace detail {
std::vector<uint8_t> read_file_as_binary(const std::string &filename,
                                         std::ostream &cerr_) {
  nowide::ifstream input_file(filename, std::ios::binary);

  if (!input_file.is_open()) {
    cerr_ << "Failed to open '" << filename << "'\n";
    return {};
  }

  input_file.unsetf(std::ios_base::skipws);

  std::vector<uint8_t> byte_vec{std::istream_iterator<uint8_t>(input_file),
                                std::istream_iterator<uint8_t>()};

  return byte_vec;
}

std::vector<uint8_t> string_to_byte_vector(const std::string &str) {
  std::vector<uint8_t> byte_vec{};

  if (!str.empty()) {
    for (const auto &c : str) {
      byte_vec.push_back(static_cast<uint8_t>(c));
    }
  }

  return byte_vec;
}
} // namespace detail

class from_console : public interface {
public:
  [[nodiscard]] const char *info() const override { return "input: console"; }

  [[nodiscard]] std::vector<uint8_t>
  read(const stream_provider &ios) const override {
    std::string input_str{};

    ios.secondary_out << "> ";
    std::getline(ios.in, input_str);

    return detail::string_to_byte_vector(input_str);
  }
};

class from_file : public interface {
public:
  explicit from_file(std::vector<std::string> names)
      : filenames(std::move(names)), iter(filenames.begin()) {}

  const char *info() const override { return "input: file"; }

  std::vector<uint8_t> read(const stream_provider &ios) const override {
    if (iter == filenames.end()) {
      return {};
    } else if (iter != filenames.begin()) {
      ios.secondary_out << "(hit enter to continue)";
      ios.in.get();
    }

    return detail::read_file_as_binary(*iter++, ios.err);
  }

private:
  const std::vector<std::string> filenames;
  mutable std::vector<std::string>::const_iterator iter;
};

class from_string : public interface {
public:
  explicit from_string(std::vector<std::string> _input)
      : input(std::move(_input)), iter(input.begin()) {}

  const char *info() const override { return "input: text"; }

  std::vector<uint8_t> read(const stream_provider &ios) const override {
    if (iter == input.end()) {
      return {};
    } else if (iter != input.begin()) {
      ios.secondary_out << "(hit enter to continue)";
      ios.in.get();
    }

    return detail::string_to_byte_vector(*iter++);
  }

private:
  const std::vector<std::string> input;
  mutable std::vector<std::string>::const_iterator iter;
};

class from_internal : public interface {
public:
  [[nodiscard]] const char *info() const override { return "input: internal"; }

  [[nodiscard]] std::vector<uint8_t>
  read(const stream_provider &ios) const override {
    return detail::string_to_byte_vector(line);
  }

  void set(const char *c_str) { line = c_str; }

private:
  std::string line{};
};

class invalid : public interface {
public:
  [[nodiscard]] const char *info() const override { return "input: invalid"; }

  [[nodiscard]] std::vector<uint8_t>
  read(const stream_provider &) const override {
    return {};
  }
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
