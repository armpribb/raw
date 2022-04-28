#pragma once

#include "types.h"

namespace print {
class engine {
public:
  PrintFunc get_print_func() const;
  PrintFunc get_queue_func();
  void print_queued();

private:
  std::vector<std::string> message_queue{};
};
} // namespace print