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
  inline void flush() {
    if (writePos) {
      fwrite(writeBuffer, 1, writePos, stdout);
      writePos = 0;
    }
    fflush(stdout);
  }

  inline ~Flusher() {
    flush();
  }
} flusher;

} // namespace io
