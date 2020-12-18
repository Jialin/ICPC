#pragma once

#include "io/read_char.h"

namespace io {

inline bool readCharArray(char* s) {
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
  *s++ = readChar(true);
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return false;
    }
    if (isspace(ch)) {
      break;
    }
    *s++ = ch;
    ++_readPos;
  }
  *s = '\0';
  return true;
}

} // namespace io
