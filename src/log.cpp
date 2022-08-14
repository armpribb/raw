#include "log.h"

#include <algorithm>

print_func logger::print() const {
  return [&](const std::string &msg) { output_stream << msg << "\n"; };
}

print_func logger::queue() {
  return [&](const std::string &msg) { message_queue.emplace_back(msg); };
}

void logger::print_queued() {
  std::for_each(message_queue.begin(), message_queue.end(), print());
  message_queue.clear();
}
