#pragma once

#include <string>

#include "types.h"

namespace output {
void write_to_clipboard(const std::string &str);
void write_to_clipboard(const std::string &str, const stream_provider_v2 &ios);
void write_to_stream(const std::string &str, const stream_provider_v2 &ios);
} // namespace output