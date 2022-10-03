#include "format_impl.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <utility>

namespace format {

namespace detail {

constexpr auto hex_prefix = "0x";

std::vector<std::string> convert_to_hex(const std::vector<uint8_t> &raw_data,
                                        const uint8_t n_byte_group) {
  std::vector<uint8_t> copy = raw_data;

  if (n_byte_group > 0 && raw_data.size() % n_byte_group) {
    const auto num_to_fill = n_byte_group - (raw_data.size() % n_byte_group);
    copy.insert(copy.begin(), num_to_fill, 0);
  }

  std::vector<std::string> hex_strings{};

  for (auto it = copy.cbegin(); it != copy.cend();) {
    std::ostringstream oss{};
    auto byte_count = n_byte_group ? n_byte_group : copy.size();
    while (byte_count-- && it != copy.cend()) {
      oss << std::setfill('0') << std::setw(2) << std::hex << unsigned(*it++);
    }
    hex_strings.push_back(oss.str());
  }

  return hex_strings;
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

  auto combine = [&byte_separator, &with_hex_prefix](const std::string &a,
                                                     const std::string &b) {
    return a + byte_separator + (with_hex_prefix ? hex_prefix : "") + b;
  };

  auto first_element =
      (with_hex_prefix ? hex_prefix : "") + hex_strings.front();

  return std::accumulate(std::next(hex_strings.begin()), hex_strings.end(),
                         first_element, combine);
}

} // namespace detail

std::string process(const std::vector<uint8_t> &raw_data,
                    const format_config &config) {
  auto hex_strings = detail::convert_to_hex(raw_data, config.n_byte_group);

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
