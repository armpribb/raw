#pragma once

#include <cstdint>
#include <vector>

#include "types.h"

namespace input {
std::vector<uint8_t> read(const std::string &str);
std::vector<uint8_t> read(const stream_provider_v2 &ios);
} // namespace input