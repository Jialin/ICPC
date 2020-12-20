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

#define FFT_UTILS_MUL_COMPLEX_VECTOR

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/fft/fft_utils.h"

const int MAXN = 1 << 15;

vector<math::Complex<double>> a, b, c;
math::FFTUtils<double> fft;

int main() {
  a.reserve(MAXN);
  b.reserve(MAXN);
  c.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    a.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
      int x;
      io::readInt(x);
      a[i].init(x, 0);
    }
    b.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
      int x;
      io::readInt(x);
      b[i].init(x, 0);
    }
    fft.mul(a, b, c);
    for (int i = 0; i <= n << 1; ++i) {
      if (i > 0) {
        io::writeChar(' ');
      }
      if (i < static_cast<int>(c.size())) {
        io::writeInt(static_cast<int64_t>(c[i].real + 0.5));
      } else {
        io::writeChar('0');
      }
    }
    io::writeChar('\n');
  }
  return 0;
}
