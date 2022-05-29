#include "mock_input.h"

#include <type_traits>

namespace input {

namespace {
std::vector<uint8_t> dummy{};
}

std::unique_ptr<input::interface>
get_input_adapter(input_type type, const std::vector<std::string> &input) {
  (void)type;
  (void)input;
  return std::make_unique<input::mock>(dummy);
}

bool _internal_set(input::interface &instance, const char *c_str) {
  (void)instance;
  (void)c_str;
  return false;
}

} // namespace input
