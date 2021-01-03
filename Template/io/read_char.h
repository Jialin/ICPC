#pragma once

namespace io {

const int _kReadBufferSize = 1 << 15;
char _readBuffer[_kReadBufferSize];
int _readPos;
int _readLength;
bool _ended = false;

inline void _loadBuffer() {
  _readLength = static_cast<int>(
      fread(_readBuffer, sizeof(char), _kReadBufferSize, stdin));
  _readPos = 0;
}

inline char readChar(bool advance = true) {
  if (_ended) {
    return 0;
  }
  if (_readPos >= _readLength) {
    _loadBuffer();
    if (_readLength == 0) {
      _ended = true;
      return 0;
    }
  }
  return _readBuffer[advance ? _readPos++ : _readPos];
}

} // namespace io
