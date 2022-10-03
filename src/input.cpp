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

std::vector<uint8_t> read(const std::string &str) {
  return detail::to_byte_vector(str);
}

std::vector<uint8_t> read(const stream_provider_v2 &ios) {
  std::string input_str{};

  ios.info << "> ";
  if (ios.in.get() != nullptr) {
    std::getline(*ios.in.get(), input_str);
  }

  return detail::to_byte_vector(input_str);
}
} // namespace input