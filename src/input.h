#pragma once

#include <cstdint>
#include <vector>

#include "stream_io.h"

namespace input {
std::vector<uint8_t> read(const std::string &str);
std::vector<uint8_t> read(streamio::instream is);
} // namespace input