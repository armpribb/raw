#include "input.h"
#include "stream_io.h"

#include <algorithm>
#include <iterator>
#include <string>

namespace input {

namespace detail {
constexpr std::vector<uint8_t> to_byte_vector(const std::string &str) {
  std::vector<uint8_t> byte_vec{};
  std::transform(str.begin(), str.end(), std::back_inserter(byte_vec),
                 [](char c) { return static_cast<uint8_t>(c); });
  return byte_vec;
}
} // namespace detail

std::vector<uint8_t> read(const std::string &str) {
  return detail::to_byte_vector(str);
}

std::vector<uint8_t> read(const streamio::istream_wrap &is) {
  std::string input_str{};

  if (is.get() != nullptr) {
    std::getline(*is.get(), input_str);
  }

  return detail::to_byte_vector(input_str);
}
} // namespace input