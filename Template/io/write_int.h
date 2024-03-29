#pragma once

#include "io/write_char.h"

namespace io {

template<class T>
inline void writeInt(T x, char c = 0, int padding = 0) {
  static char s[32];
  if (x < 0) {
    writeChar('-');
    x = -x;
  }
  int n = 0;
  while (x || !n) {
    T newX = x / 10;
    s[n++] = '0' + (x - (newX << 3) - (newX << 1));
    x = newX;
  }
  for (int i = n; i < padding; ++i) {
    writeChar('0');
  }
  for (; n > 0; writeChar(s[--n])) {}
  if (c) {
    writeChar(c);
  }
}

} // namespace io
