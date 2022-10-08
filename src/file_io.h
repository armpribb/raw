#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace fileio {

std::vector<uint8_t> read_file_as_binary(const std::string &filename);

class fstream_provider {
public:
  fstream_provider() = default;
  virtual ~fstream_provider() = default;

  virtual std::ostream *get_ostream(const std::string &filename) = 0;
  virtual std::istream *get_istream(const std::string &filename) = 0;

protected:
  fstream_provider(const fstream_provider &) = default;
  fstream_provider(fstream_provider &&) = default;
  fstream_provider &operator=(const fstream_provider &) = default;
  fstream_provider &operator=(fstream_provider &&) = default;
};

std::unique_ptr<fstream_provider> get_fstream_provider();

} // namespace fileio