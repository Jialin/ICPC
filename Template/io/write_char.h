#pragma once

#include <cstdio>

namespace io {

namespace {

const int kWriteBufferSize = 1 << 15;

int writePos = 0;
char writeBuffer[kWriteBufferSize];

} // namespace

inline void writeChar(char x) {
  if (writePos == kWriteBufferSize) {
    fwrite(writeBuffer, 1, kWriteBufferSize, stdout);
    writePos = 0;
  }
  writeBuffer[writePos++] = x;
}

struct Flusher {
  inline ~Flusher() {
    if (writePos) {
      fwrite(writeBuffer, 1, writePos, stdout);
      writePos = 0;
    }
  }
} flusher;

} // namespace io
