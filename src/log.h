#pragma once

#include "types.h"

class logger {
public:
  print_func print() const;
  queue_func queue();
  void print_queued();

private:
  std::vector<std::string> message_queue{};
};
