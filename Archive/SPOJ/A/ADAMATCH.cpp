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
#include "math/fft/fft_utils.h"
#include "math/poly/poly_int.h"

const int MAXL = 500000 + 1;
const int MAXPOW2 = 1 << 19;

int n, m;
char s[MAXL], t[MAXL];
math::PolyInt<int> a, b;
vector<int> sum;
math::FFTUtils<double> fft(MAXPOW2);

inline void calc(char c) {
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i] = s[i] == c;
  }
  b.resize(m);
  for (int i = 0, j = m - 1; i < m; ++i, --j) {
    b[i] = t[j] == c;
  }
  a.mulInline(b, true, fft);
  for (int i = 0, j = m - 1; i <= n - m && j < a.size(); ++i, ++j) {
    sum[i] += a[j];
  }
}

int main() {
  sum.reserve(MAXL);
  a.reserve(MAXPOW2);
  b.reserve(MAXPOW2);
  while (true) {
    n = io::readCharArray(s);
    if (!n) {
      break;
    }
    m = io::readCharArray(t);
    sum.assign(n - m + 1, 0);
    calc('A');
    calc('C');
    calc('T');
    calc('G');
    DEBUGV(sum);
    io::writeInt(m - *max_element(sum.begin(), sum.end()));
    io::writeChar('\n');
  }
  return 0;
}
