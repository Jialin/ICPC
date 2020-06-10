#pragma once

#include <cctype>
#include <cstdio>

namespace io {

namespace {

constexpr int kReadBufferSize = 1 << 15;
char readBuffer[kReadBufferSize];
int readPos;
int readLength;
bool ended = false;

inline void loadBuffer() {
  readLength =
      static_cast<int>(fread(readBuffer, sizeof(char), kReadBufferSize, stdin));
  readPos = 0;
}

} // namespace

inline char readChar(bool advance = true) {
  if (ended) {
    return 0;
  }
  if (readPos >= readLength) {
    loadBuffer();
    if (readLength == 0) {
      ended = true;
      return 0;
    }
  }
  return readBuffer[advance ? readPos++ : readPos];
}

} // namespace io
