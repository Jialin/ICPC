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
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define POLY_INT_ACCESS
#define POLY_INT_ACCESS_CONST
#define POLY_INT_CONSTRUCT
#define POLY_INT_MUL
#define POLY_INT_RESIZE
#define POLY_INT_SIZE
#include "math/poly/poly_int_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "math/poly/poly_int.h"

const int MAXN = 200000 + 2;
const int MAXN_05 = sqrt(MAXN) + 1;
const int MOD = 1009;

using ComplexT = double;
using Complex = math::Complex<ComplexT>;
using PolyInt = math::PolyInt<int>;

int n, m, k, k1, colorCnt[MAXN];
math::FFTUtils<ComplexT> fft(MAXN << 1);
vector<int> vs;

inline void assign(PolyInt& res, const vector<Complex>& cs) {
  res.resize(min(static_cast<int>(cs.size()), k1));
  for (size_t i = 0; i < res.size(); ++i) {
    auto v = static_cast<int64_t>(cs[i].real + 0.5);
    res[i] = v >= MOD ? v % MOD : v;
  }
}

inline PolyInt calc(int lower, int upper) {
  if (lower + 1 == upper) {
    return PolyInt(min(vs[lower] + 1, k1), 1);
  }
  int medium = (lower + upper) >> 1;
  PolyInt xs = calc(lower, medium);
  PolyInt ys = calc(medium, upper);
  assign(xs, xs.mul(ys, false, fft));
  return xs;
}

int main() {
  vs.reserve(MAXN_05);
  while (io::readInt(n) && n) {
    io::readInt(m);
    io::readInt(k);
    k1 = k + 1;
    memset(colorCnt, 0, sizeof(int) * m);
    for (int i = 0; i < n; ++i) {
      int c;
      io::readInt(c);
      ++colorCnt[c - 1];
    }
    vs.clear();
    for (int i = 0; i < m; ++i) {
      if (colorCnt[i] > 0) {
        vs.push_back(colorCnt[i]);
      }
    }
    random_shuffle(vs.begin(), vs.end());
    printf("%d\n", calc(0, vs.size())[k]);
  }
}
