#include "mock_output.h"

namespace output {

namespace {
std::string dummy{};
}

std::unique_ptr<output::interface>
get_output_adapter(output_type type, set_string_func set_result) {
  (void)type;
  return std::make_unique<output::mock>(dummy);
}

} // namespace output
