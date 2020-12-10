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
    ++readPos;
  }
  *s++ = readChar(false);
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return false;
    }
    if (isspace(ch)) {
      break;
    }
    *s++ = ch;
    ++readPos;
  }
  *s = '\0';
  return true;
}

} // namespace io
