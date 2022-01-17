#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace input {
class interface {
public:
  virtual ~interface() = default;
  virtual const char *info() const = 0;
  virtual std::vector<uint8_t> read() const = 0;
};

class from_console : public interface {
public:
  const char *info() const override { return "input: console"; }
  std::vector<uint8_t> read() const override;
};

class from_file : public interface {
public:
  from_file(const std::vector<std::string> &names) : filenames(names){};
  const char *info() const override { return "input: file"; }
  std::vector<uint8_t> read() const override;

private:
  std::string get_next_filename() const;

  std::vector<std::string> filenames;
  mutable size_t index = 0;
};

class from_internal : public interface {
public:
  const char *info() const override { return "input: internal"; };
  std::vector<uint8_t> read() const override;
  void set(const char *c_str);

private:
  std::string line{};
};

class invalid : public interface {
public:
  const char *info() const override { return "input: invalid"; }
  std::vector<uint8_t> read() const override { return {}; };
};
} // namespace input
