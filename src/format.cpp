#include "format.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

namespace format {
namespace detail {

constexpr uint8_t to_upper_offset = 32;

void convert_to_hex(std::vector<std::string> &hex_strings,
                    const std::vector<uint8_t> &raw_data,
                    const uint8_t n_byte_group) {
  std::vector<uint8_t> copy{};

  if (n_byte_group > 0 && raw_data.size() % n_byte_group) {
    const auto fill_n_byte_group =
        n_byte_group - (raw_data.size() % n_byte_group);
    const auto new_total_size = raw_data.size() + fill_n_byte_group;
    copy.reserve(new_total_size);
    copy.insert(copy.end(), fill_n_byte_group, 0);
    copy.insert(copy.end(), raw_data.begin(), raw_data.end());
  } else {
    copy = raw_data;
  }

  for (auto it = copy.cbegin(); it != copy.cend();) {
    std::ostringstream oss{};
    auto n = n_byte_group ? n_byte_group : copy.size();
    while (n-- && it != copy.cend()) {
      oss << std::setfill('0') << std::setw(2) << std::hex << unsigned(*it++);
    }
    hex_strings.emplace_back(oss.str());
  }
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
                              const std::string &byte_separator,
                              const bool print_hex_prefix) {
  std::ostringstream oss{};

  const auto last_element = std::prev(hex_strings.cend());

  for (auto it = hex_strings.cbegin(); it != hex_strings.cend(); ++it) {
    oss << (print_hex_prefix ? "0x" : "") << *it;
    if (it == last_element) {
      break;
    }
    oss << byte_separator;
  }

  return oss.str();
}
} // namespace detail

std::string engine::process(const std::vector<uint8_t> &raw_data) const {
  std::vector<std::string> hex_strings{};

  detail::convert_to_hex(hex_strings, raw_data, config.n_byte_group);

  if (config.use_uppercase) {
    detail::convert_to_uppercase(hex_strings);
  }

  const auto output_string = detail::combine_to_string(
      hex_strings, config.byte_separator, config.use_hex_prefix);

  return output_string;
}

std::unique_ptr<format::engine> get_format_engine(const format_config &config) {
  return std::make_unique<format::engine>(config);
}

} // namespace format
