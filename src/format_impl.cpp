#include "format_impl.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <sstream>
#include <utility>

namespace format {

namespace detail {

namespace {
constexpr std::vector<uint8_t>
get_padded_byte_vec(const std::vector<uint8_t> &byte_vec,
                    const uint8_t n_byte_group) {
  if (n_byte_group > 1 && byte_vec.size() % n_byte_group) {
    auto padded_byte_vec = byte_vec;
    auto num_padding_zeros = n_byte_group - (byte_vec.size() % n_byte_group);
    padded_byte_vec.insert(padded_byte_vec.begin(), num_padding_zeros, 0);
    assert(padded_byte_vec.size() % n_byte_group == 0);
    return padded_byte_vec;
  }

  return byte_vec;
}

constexpr void check_minimum_one(uint8_t &byte) {
  if (byte == 0)
    byte = 1;
  assert(byte);
}
} // namespace

std::vector<std::string>
get_grouped_hex_strings(const std::vector<uint8_t> &byte_vec,
                        uint8_t n_byte_group = 1) {
  check_minimum_one(n_byte_group);

  const auto padded_byte_vec = get_padded_byte_vec(byte_vec, n_byte_group);

  std::vector<std::string> hex_str_vec{};

  for (auto it = padded_byte_vec.begin(); it != padded_byte_vec.end();
       std::advance(it, n_byte_group)) {
    std::ostringstream oss{};
    auto to_str = [&oss](uint8_t byte) {
      oss << std::setfill('0') << std::setw(2) << std::hex << unsigned(byte);
    };
    for_each(it, std::next(it, n_byte_group), to_str);
    hex_str_vec.push_back(oss.str());
  }

  return hex_str_vec;
}

constexpr void convert_to_uppercase(std::vector<std::string> &hex_strings) {
  auto to_upper = [](std::string &hxstr) {
    std::transform(hxstr.begin(), hxstr.end(), hxstr.begin(),
                   [](unsigned char c) { return std::toupper(c); });
  };

  std::for_each(hex_strings.begin(), hex_strings.end(), to_upper);
}

constexpr std::string
combine_to_string(const std::vector<std::string> &hex_strings,
                  const std::string &byte_separator,
                  const bool with_hex_prefix) {
  if (hex_strings.empty())
    return {};

  const auto prefix = with_hex_prefix ? "0x" : "";

  auto combine = [&byte_separator, &prefix](const std::string &a,
                                            const std::string &b) {
    return a + byte_separator + prefix + b;
  };

  const auto first_element = prefix + hex_strings.front();

  return std::accumulate(std::next(hex_strings.begin()), hex_strings.end(),
                         first_element, combine);
}

} // namespace detail

std::string process(const std::vector<uint8_t> &raw_data,
                    const format_config &config) {
  auto hex_strings =
      detail::get_grouped_hex_strings(raw_data, config.n_byte_group);

  if (config.use_uppercase) {
    detail::convert_to_uppercase(hex_strings);
  }

  return detail::combine_to_string(hex_strings, config.byte_separator,
                                   config.use_hex_prefix);
}

std::string engine::process(const std::vector<uint8_t> &raw_data) const {
  return format::process(raw_data, config);
}

std::unique_ptr<format::interface>
get_format_engine(const format_config &config) {
  return std::make_unique<format::engine>(config);
}

} // namespace format
