#include "output_adapter.h"

#include <memory>
#include <nowide/iostream.hpp>

namespace output {
void to_clipboard::write(const std::string &str) const {
  impl->copy_to_clipboard(str);
  nowide::cout << "<result copied to clipboard>\n";
}

void to_console::write(const std::string &str) const {
  nowide::cout << "< " << str << "\n";
}

void to_file::write(const std::string &str) const {
  nowide::cout << "<not implemented yet>\n";
}

std::unique_ptr<output::interface> get_output_adapter(output_type type) {
  switch (type) {
  case output_type::clipboard:
    return std::make_unique<output::to_clipboard>();
  case output_type::console:
    return std::make_unique<output::to_console>();
  case output_type::file:
    return std::make_unique<output::to_file>();
  default:
    return std::make_unique<output::invalid>();
  }
}
} // namespace output
