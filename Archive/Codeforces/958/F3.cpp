// First batch includes
#include "common/include.h"
#include "common/macros.h"

#define FFT_POLY_CONSTRUCT
#define FFT_POLY_MUL_INLINE
#include "math/poly/fft_poly_macros.h"

#include "io/read_int.h"
#include "math/poly/fft_poly.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000 + 2;
const int MAXN_05 = sqrt(MAXN) + 1;
const int MOD = 1009;

using POLY_T = double;
using FFT_T = double;
using Complex = math::Complex<FFT_T>;
using FFTPoly = math::FFTPoly<POLY_T, FFT_T>;

int n, m, k, k1, colorCnt[MAXN];
vector<int> vs;

inline void assign(FFTPoly& res, const vector<Complex>& cs) {
  res.resize(min(static_cast<int>(cs.size()), k1));
  for (size_t i = 0; i < res.size(); ++i) {
    auto v = static_cast<int64_t>(cs[i].real + 0.5);
    res[i] = v >= MOD ? v % MOD : v;
  }
}

inline FFTPoly calc(int lower, int upper) {
  if (lower + 1 == upper) {
    return FFTPoly(min(vs[lower] + 1, k1), 1);
  }
  int medium = (lower + upper) >> 1;
  FFTPoly xs = calc(lower, medium);
  FFTPoly ys = calc(medium, upper);
  assign(xs, math::FFTMulUtils<FFT_T>::instance().mulReal(xs, ys, false));
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
    printf("%d\n", static_cast<int>(calc(0, vs.size())[k]));
  }
}
