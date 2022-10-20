#pragma once

#include <istream>
#include <ostream>

#include "file_io.h"
#include "types.h"

namespace streamio {

class outstream {
public:
  outstream() = default;
  outstream(std::ostream *ptr) : ostream_ptr(ptr) {}

  template <typename T> const outstream &operator<<(const T &obj) const {
    if (ostream_ptr) {
      *ostream_ptr << obj;
    }
    return *this;
  }
  std::ostream *get() const { return ostream_ptr; }

private:
  std::ostream *ostream_ptr = nullptr;
};

class instream {
public:
  instream() = default;
  instream(std::istream *ptr) : istream_ptr(ptr) {}

  template <typename T> const instream &operator>>(T &obj) const {
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
  outstream err;
  instream in;
  outstream info;
  outstream out;
  instream prompt;
};

provider get_provider(fileio::provider &fileio, const convert_config &config);

} // namespace streamio
