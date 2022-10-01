#include "output_adapter.h"

#include <memory>
#include <utility>

#include "clipboard_impl.h"

namespace output {

class to_clipboard : public interface {
public:
  to_clipboard() : impl(std::make_unique<clipboard_impl>()){};

  [[nodiscard]] const char *info() const override {
    return "output: clipboard";
  }

  void write(const std::string &str,
             const stream_provider &ios) const override {
    impl->copy_to_clipboard(str, ios.err);
    ios.secondary_out << "<result copied to clipboard>\n";
  }

private:
  std::unique_ptr<clipboard_impl> impl;
};

class to_console : public interface {
public:
  [[nodiscard]] const char *info() const override { return "output: console"; }

  void write(const std::string &str,
             const stream_provider &ios) const override {
    ios.secondary_out << "< ";
    ios.out << str << "\n";
  }
};

class to_file : public interface {
public:
  [[nodiscard]] const char *info() const override { return "output: file"; }

  void write(const std::string &str,
             const stream_provider &ios) const override {
    ios.secondary_out << "<not implemented yet>\n";
  }
};

class to_string : public interface {
public:
  explicit to_string(set_string_func set) : set_result(std::move(set)) {}

  [[nodiscard]] const char *info() const override { return "output: string"; }

  void write(const std::string &str,
             const stream_provider &ios) const override {
    if (!set_result) {
      ios.err << "error: no 'set_string' function provided\n";
      return;
    }

    try {
      set_result(str);
    } catch (std::bad_function_call &e) {
      ios.err << e.what() << "\n";
    }
  }

private:
  set_string_func set_result;
};

class invalid : public interface {
  [[nodiscard]] const char *info() const override { return "output: invalid"; }

  void write(const std::string &, const stream_provider &) const override {}
};

std::unique_ptr<output::interface>
get_output_adapter(output_type type, set_string_func set_result) {
  switch (type) {
  case output_type::clipboard:
    return std::make_unique<output::to_clipboard>();
  case output_type::console:
    return std::make_unique<output::to_console>();
  case output_type::file:
    return std::make_unique<output::to_file>();
  case output_type::string:
    return std::make_unique<output::to_string>(set_result);
  default:
    return std::make_unique<output::invalid>();
  }
}

} // namespace output
