#pragma once

#include <memory>
#include <string>

#include "clipboard_impl.h"

namespace output {
class interface {
public:
  virtual void write(const std::string &str) const = 0;
};

class to_clipboard : public interface {
public:
  to_clipboard() : impl(std::make_unique<clipboard_impl>()){};
  void write(const std::string &str) const override;

private:
  std::unique_ptr<clipboard_impl> impl;
};

class to_console : public interface {
public:
  void write(const std::string &str) const override;
};

class to_file : public interface {
public:
  void write(const std::string &str) const override;
};
} // namespace output
