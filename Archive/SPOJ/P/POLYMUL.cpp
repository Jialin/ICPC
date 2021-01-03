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

#define POLY_INT_ACCESS
#define POLY_INT_MUL_INLINE
#define POLY_INT_RESERVE
#define POLY_INT_RESIZE
#define POLY_INT_SIZE
#include "math/poly/poly_int_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/poly/poly_int.h"

const int MAXPOW2 = 1 << 15;

math::PolyInt<int64_t> a, b;
math::FFTUtils<double> fft(MAXPOW2);

int main() {
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
    a.mulInline(b, false, fft);
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
