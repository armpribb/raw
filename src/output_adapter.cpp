#include "output_adapter.h"

#include <nowide/iostream.hpp>

namespace output {
void to_clipboard::write(const std::string &str) const {
  impl->copy_to_clipboard(str);
}

void to_console::write(const std::string &str) const {
  nowide::cout << str << "\n";
}

void to_file::write(const std::string &str) const { (void)str; }
} // namespace output