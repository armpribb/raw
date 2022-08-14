#pragma once

#include "format.h"

namespace format {

class engine : public interface {
public:
  engine() = default;
  engine(format_config cnf) : config(std::move(cnf)){};

  std::string process(const std::vector<uint8_t> &raw_data) const override;

private:
  format_config config{};
};

} // namespace format
