#pragma once

#include "file_io.h"
#include "types.h"

namespace config {

streamio::provider get_stream_provider(fileio::provider &fileio,
                                       const convert_config &config);
}