#pragma once

#include <memory>
#include <string>
#include <vector>

namespace fileio {

std::vector<uint8_t> read_file_as_binary(const std::string &filename);

class provider {
public:
  provider() = default;
  virtual ~provider() = default;

  virtual std::ostream *get_ostream(const std::string &filename) = 0;
  virtual std::istream *get_istream(const std::string &filename) = 0;

protected:
  provider(const provider &) = default;
  provider(provider &&) = default;
  provider &operator=(const provider &) = default;
  provider &operator=(provider &&) = default;
};

std::unique_ptr<provider> get_fstream_provider();

} // namespace fileio