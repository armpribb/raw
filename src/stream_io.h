#pragma once

#include <istream>
#include <ostream>

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

  constexpr operator bool() const { return ostream_ptr != nullptr; }

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

  constexpr operator bool() const { return istream_ptr != nullptr; }

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

} // namespace streamio
