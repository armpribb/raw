#pragma once

#include "types.h"

#include <ostream>

class logger {
public:
  explicit logger(std::ostream &ostr) : output_stream(ostr) {}
  [[nodiscard]] print_func print() const;
  print_func queue();
  void print_queued();

private:
  std::ostream &output_stream;
  std::vector<std::string> message_queue{};
};
