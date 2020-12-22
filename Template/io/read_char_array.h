#pragma once

#include "io/read_char.h"

namespace io {

inline int readCharArray(char* s) {
  char ch;
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return 0;
    }
    if (!isspace(ch)) {
      break;
    }
    ++_readPos;
  }
  *s++ = readChar(true);
  int res = 1;
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return res;
    }
    if (isspace(ch)) {
      break;
    }
    *s++ = ch;
    ++res;
    ++_readPos;
  }
  *s = '\0';
  return res;
}

} // namespace io
