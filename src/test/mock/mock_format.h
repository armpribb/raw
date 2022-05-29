#pragma once

#include <format.h>

namespace format {

class mock : public interface {
public:
  explicit mock(std::string &inject, std::vector<uint8_t> &read)
      : format_injection(inject), read_input(read) {}
  std::string process(const std::vector<uint8_t> &raw_data) const override;

private:
  std::string &format_injection;
  std::vector<uint8_t> &read_input;
};

} // namespace format
