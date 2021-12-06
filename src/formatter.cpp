#include "formatter.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

namespace format {
namespace detail {

constexpr uint8_t to_upper_offset = 32;

void convert_to_hex(std::vector<std::string> &hex_strings,
                    const std::vector<uint8_t> &raw_data,
                    bool print_hex_prefix) {
  auto to_hex = [&hex_strings, print_hex_prefix](auto c) {
    std::ostringstream oss{};
    if (print_hex_prefix) {
      oss << "0x";
    }
    oss << std::setfill('0') << std::setw(2) << std::hex << unsigned(c);
    hex_strings.push_back(oss.str());
  };

  std::for_each(raw_data.cbegin(), raw_data.cend(), to_hex);
}

void convert_to_uppercase(std::vector<std::string> &hex_strings) {
  auto to_upper = [&hex_strings](std::string &hxstr) {
    for (char &c : hxstr) {
      if (c >= 'a' && c <= 'f') {
        c -= to_upper_offset;
      }
    }
  };

  std::for_each(hex_strings.begin(), hex_strings.end(), to_upper);
}

std::string combine_to_string(const std::vector<std::string> &hex_strings,
                              const std::string &byte_separator) {
  std::ostringstream oss{};

  const auto last_element = std::prev(hex_strings.cend());

  for (auto it = hex_strings.cbegin(); it != hex_strings.cend(); ++it) {
    oss << *it;
    if (it == last_element) {
      break;
    }
    oss << byte_separator;
  }

  return oss.str();
}
} // namespace detail

std::string engine::process(const std::vector<uint8_t> &raw_data) {
  std::vector<std::string> hex_strings{};

  detail::convert_to_hex(hex_strings, raw_data, use_hex_prefix);

  if (use_uppercase) {
    detail::convert_to_uppercase(hex_strings);
  }

  auto output_string = detail::combine_to_string(hex_strings, byte_separator);

  return output_string;
}
} // namespace format
