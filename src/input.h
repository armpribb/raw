#pragma once

#include "stream_io.h"

#include <cstdint>
#include <string>
#include <vector>

namespace input {
std::vector<uint8_t> read_string(const std::string &str,
                                 bool little_endian = false);
std::vector<uint8_t> read_stream(streamio::instream in,
                                 bool little_endian = false);
} // namespace input