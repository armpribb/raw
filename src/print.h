#pragma once

#include "types.h"

namespace print {
class engine {
public:
  print_func get_print_func() const;
  print_func get_queue_func();
  void print_queued();

private:
  std::vector<std::string> message_queue{};
};
} // namespace print