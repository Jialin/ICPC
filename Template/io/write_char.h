#pragma once

namespace io {

const int _kWriteBufferSize = 1 << 15;

int _writePos = 0;
char _writeBuffer[_kWriteBufferSize];

inline void writeChar(char x) {
  if (_writePos == _kWriteBufferSize) {
    fwrite(_writeBuffer, 1, _kWriteBufferSize, stdout);
    _writePos = 0;
  }
  _writeBuffer[_writePos++] = x;
}

struct _Flusher {
  inline void flush() {
    if (_writePos) {
      fwrite(_writeBuffer, 1, _writePos, stdout);
      _writePos = 0;
    }
    fflush(stdout);
  }

  inline ~_Flusher() {
    flush();
  }
} _flusher;

} // namespace io
