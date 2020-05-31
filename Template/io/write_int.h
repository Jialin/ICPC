#include <cstdio>

namespace io {

namespace {

constexpr int kWriteBufferSize = 1 << 15;

static int writePos = 0;
static char writeBuffer[kWriteBufferSize];

} // namespace

inline void writeChar(int x) {
  if (writePos == kWriteBufferSize) {
    fwrite(writeBuffer, 1, kWriteBufferSize, stdout);
    writePos = 0;
  }
  writeBuffer[writePos++] = static_cast<char>(x);
}

template<class T>
inline void writeInt(T x) {
  if (x < 0) {
    writeChar('-'), x = -x;
  }
  static char s[24];
  int n = 0;
  while (x || !n) {
    s[n++] = '0' + x % 10, x /= 10;
  }
  while (n--) {
    writeChar(s[n]);
  }
}

struct Flusher {
  ~Flusher() {
    if (writePos) {
      fwrite(writeBuffer, 1, writePos, stdout);
      writePos = 0;
    }
  }
} flusher;

} // namespace io
