#include "input.h"

#include <algorithm>
#include <iterator>

namespace input {

namespace detail {
constexpr std::vector<uint8_t> to_byte_vector(const std::string &str) {
  std::vector<uint8_t> byte_vec{};
  std::transform(str.begin(), str.end(), std::back_inserter(byte_vec),
                 [](char c) { return static_cast<uint8_t>(c); });
  return byte_vec;
}
} // namespace detail

std::vector<uint8_t> read_string(const std::string &str, bool little_endian) {
  auto raw_data = detail::to_byte_vector(str);

  if (little_endian)
    std::reverse(raw_data.begin(), raw_data.end());

  return raw_data;
}

std::vector<uint8_t> read_stream(streamio::instream in, bool little_endian) {
  std::string input_str{};

  if (in) {
    std::getline(*in.get(), input_str);
  }

  return read_string(input_str, little_endian);
}
} // namespace input