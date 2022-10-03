#include "mock_format.h"

namespace format {

namespace {
std::string dummy_inject{"0xDU, 0xMM, 0xYF, 0xOR, 0xMA, 0xT!"};
std::vector<uint8_t> dummy_read{};
} // namespace

std::string process(const std::vector<uint8_t> &raw_data,
                    const format_config &) {
  format::mock formatter{dummy_inject, dummy_read};
  return formatter.process(raw_data);
}

std::string mock::process(const std::vector<uint8_t> &raw_data) const {
  read_input = raw_data;
  return format_injection;
}

std::unique_ptr<format::interface>
get_format_engine(const format_config &config) {
  (void)config;
  return std::make_unique<format::mock>(dummy_inject, dummy_read);
}

} // namespace format