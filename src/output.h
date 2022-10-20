#pragma once

#include <string>

#include "stream_io.h"

namespace output {
void write_to_clipboard(const std::string &str);
void write_to_clipboard(const std::string &str,
                        const streamio::provider &ios);
void write_to_stream(const std::string &str,
                     const streamio::provider &ios);
} // namespace output