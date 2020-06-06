#pragma once

#include <cctype>
#include <cstdio>

namespace io {

namespace {

constexpr int kBufferSize = 1 << 15;
char buffer[kBufferSize];
int pos, len;
bool ended = false;

inline void loadBuffer() {
  len = static_cast<int>(fread(buffer, sizeof(char), kBufferSize, stdin));
  pos = 0;
}

inline char nextChar(bool advance = true) {
  if (ended) {
    return 0;
  }
  if (pos >= len) {
    loadBuffer();
    if (len == 0) {
      ended = true;
      return 0;
    }
  }
  return buffer[advance ? pos++ : pos];
}

} // namespace

template<typename T>
inline bool readInt(T& res) {
  char ch;
  while (true) {
    ch = nextChar(false);
    if (!ch) {
      return false;
    }
    if (!isspace(ch)) {
      break;
    }
    ++pos;
  }
  ch = nextChar(false);
  bool negative = ch == '-';
  if (negative) {
    ++pos;
  }
  res = 0;
  while (true) {
    ch = nextChar(false);
    if (!isdigit(ch)) {
      break;
    }
    res = res * 10 + (ch - '0');
    ++pos;
  }
  if (negative) {
    res = -res;
  }
  return true;
}

} // namespace io
