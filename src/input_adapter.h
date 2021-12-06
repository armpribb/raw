#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace input {
class interface {
public:
  virtual std::vector<uint8_t> read() const = 0;
};

class from_console : public interface {
public:
  std::vector<uint8_t> read() const override;
};

class from_file : public interface {
public:
  from_file(const std::vector<std::string> &names) : filenames(names){};
  std::vector<uint8_t> read() const override;

private:
  std::string get_next_filename() const;

  std::vector<std::string> filenames;
  mutable size_t index = 0;
};
} // namespace input
