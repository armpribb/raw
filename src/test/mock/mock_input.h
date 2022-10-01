#pragma once

#include <input_adapter.h>

namespace input {

class mock : public interface {
public:
  explicit mock(std::vector<uint8_t> &inject) : input_injection(inject) {}
  [[nodiscard]] const char *info() const override { return "input: mock"; }
  [[nodiscard]] std::vector<uint8_t>
  read(const stream_provider &ios) const override {
    return input_injection;
  }

private:
  std::vector<uint8_t> &input_injection;
};

} // namespace input
