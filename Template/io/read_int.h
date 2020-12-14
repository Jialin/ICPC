#pragma once

#include "io/read_char.h"

namespace io {

template<typename T>
inline bool readInt(T& res) {
  char ch;
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return false;
    }
    if (!isspace(ch)) {
      break;
    }
    ++_readPos;
  }
  ch = readChar(false);
  bool negative = ch == '-';
  if (negative) {
    ++_readPos;
  }
  res = 0;
  while (true) {
    ch = readChar(false);
    if (!isdigit(ch)) {
      break;
    }
    res = (res << 3) + (res << 1) + (ch & 15);
    ++_readPos;
  }
  if (negative) {
    res = -res;
  }
  return true;
}

} // namespace io
