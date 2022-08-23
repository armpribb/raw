#pragma once

#include <input_adapter.h>

namespace input {

class mock : public interface {
public:
  explicit mock(std::vector<uint8_t> &inject) : input_injection(inject) {}
  const char *info() const override { return "input: mock"; }
  std::vector<uint8_t> read(const stream_provider &ios) const override { return input_injection; }

private:
  std::vector<uint8_t> &input_injection;
};

} // namespace input
