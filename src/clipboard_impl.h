#pragma once

#include <ostream>
#include <string>

namespace output {
class clipboard_impl {
public:
  void copy_to_clipboard(const std::string &str, std::ostream &_cerr) const;
};
} // namespace output
