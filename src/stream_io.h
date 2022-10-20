#pragma once

#include <istream>
#include <ostream>

#include "file_io.h"
#include "types.h"

namespace streamio {

class ostream_wrap {
public:
  ostream_wrap() = default;
  ostream_wrap(std::ostream *ptr) : ostream_ptr(ptr) {}

  template <typename T> const ostream_wrap &operator<<(const T &obj) const {
    if (ostream_ptr) {
      *ostream_ptr << obj;
    }
    return *this;
  }
  std::ostream *get() const { return ostream_ptr; }

private:
  std::ostream *ostream_ptr = nullptr;
};

class istream_wrap {
public:
  istream_wrap() = default;
  istream_wrap(std::istream *ptr) : istream_ptr(ptr) {}

  template <typename T> const istream_wrap &operator>>(T &obj) const {
    if (istream_ptr) {
      *istream_ptr >> obj;
    }
    return *this;
  }
  std::istream *get() const { return istream_ptr; }

private:
  std::istream *istream_ptr = nullptr;
};

struct provider {
  ostream_wrap err;
  istream_wrap in;
  ostream_wrap info;
  ostream_wrap out;
  istream_wrap prompt;
};

provider get_stream_provider(fileio::provider &fileio,
                             const convert_config_v2 &config);

} // namespace streamio
