#pragma once

#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace format {

std::string process(const std::vector<uint8_t> &raw_data,
                    const format_config &config = {});

} // namespace format
