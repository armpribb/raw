#pragma once

#include <string>

namespace output {
class clipboard_impl {
public:
  void copy_to_clipboard(const std::string &str) const;
};
} // namespace output
