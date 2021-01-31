#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define FFT_POLY_MUL_INLINE
#include "math/poly/fft_poly_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/poly/fft_poly.h"

const int MAXPOW2 = 1 << 15;

using FFT_T = double;

math::FFTPoly<int64_t, FFT_T> a, b;

int main() {
  math::FFTUtils<FFT_T>::instance().initCapacity(MAXPOW2);
  a.reserve(MAXPOW2);
  b.reserve(MAXPOW2);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    a.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
      io::readInt(a[i]);
    }
    b.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
      io::readInt(b[i]);
    }
    a *= b;
    for (int i = 0; i <= n << 1; ++i) {
      if (i > 0) {
        io::writeChar(' ');
      }
      if (i < a.size()) {
        io::writeInt(a[i]);
      } else {
        io::writeChar('0');
      }
    }
    io::writeChar('\n');
  }
  return 0;
}
