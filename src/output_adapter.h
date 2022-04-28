#pragma once

#include <memory>
#include <string>

#include "clipboard_impl.h"
#include "types.h"

namespace output {
class interface {
public:
  virtual ~interface() = default;
  virtual const char *info() const = 0;
  virtual void write(const std::string &str) const = 0;
};

class to_clipboard : public interface {
public:
  to_clipboard() : impl(std::make_unique<clipboard_impl>()){};
  const char *info() const override { return "output: clipboard"; }
  void write(const std::string &str) const override;

private:
  std::unique_ptr<clipboard_impl> impl;
};

class to_console : public interface {
public:
  const char *info() const override { return "output: console"; }
  void write(const std::string &str) const override;
};

class to_file : public interface {
public:
  const char *info() const override { return "output: file"; }
  void write(const std::string &str) const override;
};

class invalid : public interface {
  const char *info() const override { return "output: invalid"; }
  void write(const std::string &) const override {}
};

std::unique_ptr<output::interface> get_output_adapter(output_type type);

} // namespace output
