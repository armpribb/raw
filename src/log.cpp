#include "log.h"

#include <algorithm>
#include <nowide/iostream.hpp>

print_func logger::print() const {
  return [](const std::string &msg) { nowide::cout << msg << "\n"; };
}

queue_func logger::queue() {
  return [this](const std::string &msg) { message_queue.emplace_back(msg); };
}

void logger::print_queued() {
  std::for_each(message_queue.begin(), message_queue.end(), print());
  message_queue.clear();
}
