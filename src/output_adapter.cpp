#include "output_adapter.h"

#include <memory>

#include "clipboard_impl.h"

namespace output {

class to_clipboard : public interface {
public:
  to_clipboard() : impl(std::make_unique<clipboard_impl>()){};

  [[nodiscard]] const char *info() const override {
    return "output: clipboard";
  }

  void write(const std::string &str, std::ostream &cout) const override {
    impl->copy_to_clipboard(str);
    cout << "<result copied to clipboard>\n";
  }

private:
  std::unique_ptr<clipboard_impl> impl;
};

class to_console : public interface {
public:
  [[nodiscard]] const char *info() const override { return "output: console"; }

  void write(const std::string &str, std::ostream &cout) const override {
    cout << "< " << str << "\n";
  }
};

class to_file : public interface {
public:
  [[nodiscard]] const char *info() const override { return "output: file"; }

  void write(const std::string &str, std::ostream &cout) const override {
    cout << "<not implemented yet>\n";
  }
};

class invalid : public interface {
  [[nodiscard]] const char *info() const override { return "output: invalid"; }

  void write(const std::string &, std::ostream &) const override {}
};

std::unique_ptr<output::interface> get_output_adapter(output_type type) {
  switch (type) {
  case output_type::clipboard:
    return std::make_unique<output::to_clipboard>();
  case output_type::console:
    return std::make_unique<output::to_console>();
  case output_type::file:
    return std::make_unique<output::to_file>();
  default:
    return std::make_unique<output::invalid>();
  }
}

} // namespace output
