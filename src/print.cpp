#include "print.h"

#include <algorithm>
#include <nowide/iostream.hpp>

namespace print {

print_func engine::get_print_func() const {
  return [](const std::string &msg) { nowide::cout << msg << "\n"; };
}

print_func engine::get_queue_func() {
  return [this](const std::string &msg) { message_queue.emplace_back(msg); };
}

void engine::print_queued() {
  std::for_each(message_queue.begin(), message_queue.end(), get_print_func());
  message_queue.clear();
}
} // namespace print
