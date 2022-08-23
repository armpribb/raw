#pragma once

#include <output_adapter.h>

namespace output {

class mock : public interface {
public:
  explicit mock(std::string &str) : output_str(str) {}
  const char *info() const override { return "output: mock"; }
  void write(const std::string &str,
             const stream_provider &iostream) const override { output_str = str; }

private:
  std::string &output_str;
};

} // namespace output
