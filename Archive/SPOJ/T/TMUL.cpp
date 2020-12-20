// clang-format off
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
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
template<typename T>
inline bool readInt(T& res) {
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
  ch = readChar(false);
  bool negative = ch == '-';
  if (negative) {
    ++_readPos;
  }
  res = 0;
  while (true) {
    ch = readChar(false);
    if (!isdigit(ch)) {
      break;
    }
    res = (res << 3) + (res << 1) + (ch & 15);
    ++_readPos;
  }
  if (negative) {
    res = -res;
  }
  return true;
}
} // namespace io
namespace math {
template<typename T = double>
struct Complex {
  inline Complex(T _real = 0, T _imag = 0) : real(_real), imag(_imag) {}
  inline void operator+=(const Complex<T>& o) {
    real += o.real;
    imag += o.imag;
  }
  inline void operator/=(T scale) {
    real /= scale;
    imag /= scale;
  }
  inline void init(T _real = 0, T _imag = 0) {
    real = _real;
    imag = _imag;
  }
  inline void initPolar(T r, T theta) {
    real = r * cos(theta);
    imag = r * sin(theta);
  }
  inline void initMul(const Complex<T>& x, const Complex<T>& y) {
    real = x.real * y.real - x.imag * y.imag;
    imag = x.real * y.imag + x.imag * y.real;
  }
  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real = x.real - y.real;
    imag = x.imag - y.imag;
  }
  T real, imag;
};
const int POW10[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
} // namespace math
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
template<class T>
inline void writeInt(T x, int padding = 0) {
  static char s[32];
  if (x < 0) {
    writeChar('-');
    x = -x;
  }
  int n = 0;
  for (; x || !n; x /= 10) {
    s[n++] = '0' + x % 10;
  }
  for (int i = n; i < padding; ++i) {
    writeChar('0');
  }
  for (; n > 0; writeChar(s[--n])) {}
}
} // namespace io
namespace math {
template<int GROUP = 9, typename BASE_SQR = int64_t>
struct BigInt {
  inline void initCapacity(int capacity = -1) {
    if (capacity >= 0) {
      _vs.reserve((capacity + GROUP - 1) / GROUP);
    }
  }
  inline void initCharArray(const char* s, int size = -1) {
    _vs.clear();
    for (int i = (size >= 0 ? size : strlen(s)) - 1; i >= 0; i -= GROUP) {
      int v = 0;
      for (int j = min(i, GROUP - 1); j >= 0; --j) {
        v = v * 10 + s[i - j] - '0';
      }
      _vs.push_back(v);
    }
    clean();
  }
  inline void clean() {
    for (; _vs.size() > 1 && !_vs.back(); _vs.pop_back()) {}
  }
  template<typename T>
  inline void operator=(const vector<Complex<T> >& o) {
    _vs.reserve(o.size() + 1);
    _vs.clear();
    BASE_SQR carry = 0;
    for (size_t i = 0; i < o.size() || carry; ++i) {
      if (i == _vs.size()) {
        _vs.push_back(0);
      }
      if (i < o.size()) {
        carry += o[i].real + 0.5;
      }
      _vs[i] = carry % POW10[GROUP];
      carry /= POW10[GROUP];
    }
    clean();
  }
  inline void outputFast() const {
    int idx = static_cast<int>(_vs.size()) - 1;
    io::writeInt(_vs[idx]);
    for (int i = idx - 1; i >= 0; --i) {
      io::writeInt(_vs[i], GROUP);
    }
  }
  template<typename T>
  inline void outputComplexVector(vector<Complex<T> >& res) const {
    res.resize(_vs.size());
    for (size_t i = 0; i < _vs.size(); ++i) {
      res[i].init(_vs[i], 0);
    }
  }
  vector<int> _vs;
};
inline uint32_t nextPow2_32(uint32_t v) {
  if (!v) {
    return 1;
  }
  uint32_t res = 1U << (31 - __builtin_clz(v));
  return res == v ? res : res << 1;
}
template<typename T = double>
struct FFTUtils {
  inline FFTUtils(int capacity = -1) {
    _ws.clear();
    _revs.clear();
    if (capacity > 0) {
      capacity = nextPow2_32(capacity);
      _cs1.reserve(capacity);
      _cs2.reserve(capacity);
      _cs3.reserve(capacity);
    }
  }
  template<int GROUP, typename BASE_SQR>
  inline void
  mul(const BigInt<GROUP, BASE_SQR>& x,
      const BigInt<GROUP, BASE_SQR>& y,
      BigInt<GROUP, BASE_SQR>& res) {
    x.outputComplexVector(_cs1);
    y.outputComplexVector(_cs2);
    mul(_cs1, _cs2, _cs3);
    res = _cs3;
  }
  inline void
  mul(vector<Complex<T> >& x, vector<Complex<T> >& y, vector<Complex<T> >& res) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    _expand(pow2, x);
    _expand(pow2, y);
    fft(pow2, x, false);
    fft(pow2, y, false);
    res.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      res[i].initMul(x[i], y[i]);
    }
    fft(pow2, res, true);
    _shrink(res);
  }
  inline void fft(int pow2, vector<Complex<T> >& cs, bool invert) {
    _initSize(pow2);
    const vector<int>& rev = _revs[pow2];
    for (int i = 0; i < pow2; ++i) {
      if (i < rev[i]) {
        swap(cs[i], cs[rev[i]]);
      }
    }
    const vector<Complex<T> >& w = _ws[pow2];
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0, l2 = l << 1, step = pow2 / l2; i < pow2; i += l2) {
        for (int j = 0, wIdx = invert ? pow2 : 0; j < l;
             ++j, wIdx += invert ? -step : step) {
          _c.initMul(cs[i + j + l], w[wIdx]);
          cs[i + j + l].initSub(cs[i + j], _c);
          cs[i + j] += _c;
        }
      }
    }
    if (invert) {
      for (int i = 0; i < pow2; ++i) {
        cs[i] /= pow2;
      }
    }
  }
  inline void _initSize(int pow2) {
    if (_ws.count(pow2)) {
      return;
    }
    vector<Complex<T> >& w = _ws[pow2];
    w.resize(pow2 + 1);
    w[0].init(1, 0);
    vector<int>& rev = _revs[pow2];
    rev.resize(pow2);
    T angle = acos(static_cast<T>(-1)) * 2 / pow2;
    _c.initPolar(1, angle);
    int logN = __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      w[i + 1].initMul(w[i], _c);
      rev[i] = 0;
      for (int j = i; j; j &= j - 1) {
        rev[i] |= 1 << (logN - 1 - __builtin_ctz(j));
      }
    }
  }
  inline void _expand(int n, vector<Complex<T> >& cs) {
    for (int i = cs.size(); i < n; ++i) {
      cs.push_back(Complex<T>(0, 0));
    }
  }
  inline void _shrink(vector<Complex<T> >& cs) {
    for (; cs.size() > 1 && T(cs.back().real) < 0.5; cs.pop_back()) {}
  }
  map<int, vector<Complex<T> > > _ws;
  map<int, vector<int> > _revs;
  Complex<T> _c;
  vector<Complex<T> > _cs1, _cs2, _cs3;
};
} // namespace math
const int GROUP = 3;
const int MAXL = 10000 + GROUP * 5;
math::FFTUtils<double> fft((MAXL / GROUP) << 1);
math::BigInt<GROUP, int> a, b, c;
char s1[MAXL], s2[MAXL];
int main() {
  a.initCapacity(MAXL << 1);
  b.initCapacity(MAXL << 1);
  c.initCapacity(MAXL << 1);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readCharArray(s1);
    io::readCharArray(s2);
    a.initCharArray(s1);
    b.initCharArray(s2);
    fft.mul(a, b, c);
    c.outputFast();
    io::writeChar('\n');
  }
  return 0;
}
