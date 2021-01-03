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
#include "io/read_char_array.h"
#include "io/write_int.h"
#include "math/poly/poly_int.h"

const int MAXPOW2 = 1 << 18;
const int MAXL = 100000 + 1;

vector<int> sum;
int n, n2_1;
char s[MAXL];
math::PolyInt<int> xs, ys;
math::FFTUtils<double> fft(MAXPOW2);

inline void calc(char c) {
  xs.resize(n - 1);
  ys.resize(n);
  for (int i = 1; i < n; ++i) {
    xs[i - 1] = s[i] == c;
  }
  for (int i = 0; i < n; ++i) {
    ys[n - 1 - i] = s[i] == c;
  }
  xs.mulInline(ys, false, fft);
  for (int i = 0, j = n - 1; i < n && j < xs.size(); ++i, ++j) {
    sum[i] += xs[j];
  }
}

int main() {
  xs.reserve(MAXPOW2);
  ys.reserve(MAXPOW2);
  while (io::readCharArray(s)) {
    n = strlen(s);
    sum.assign(n, 0);
    calc('a');
    calc('b');
    calc('c');
    int res = *max_element(sum.begin(), sum.end());
    io::writeInt(res);
    io::writeChar('\n');
    bool first = true;
    for (int i = 0; i < n; ++i) {
      if (sum[i] != res) {
        continue;
      }
      if (!first) {
        io::writeChar(' ');
      }
      first = false;
      io::writeInt(i + 1);
    }
    io::writeChar('\n');
  }
}
