#pragma once

#include "io/write_char.h"

namespace io {

template<class T>
inline void writeInt(T x) {
  static char s[32];
  if (x < 0) {
    writeChar('-');
    x = -x;
  }
  int n = 0;
  for (; x || !n; x /= 10) {
    s[n++] = '0' + x % 10;
  }
  for (; n > 0; writeChar(s[--n])) {}
}

} // namespace io
