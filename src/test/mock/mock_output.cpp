#include "mock_output.h"

namespace output {

namespace {
std::string dummy{};
}

std::unique_ptr<output::interface> get_output_adapter(output_type type) {
  (void)type;
  return std::make_unique<output::mock>(dummy);
}

} // namespace output
