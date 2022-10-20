#pragma once

#include <cstdint>
#include <vector>

#include "stream_io.h"

namespace input {
std::vector<uint8_t> read(const std::string &str);
std::vector<uint8_t> read(const streamio::istream_wrap &is);
} // namespace input