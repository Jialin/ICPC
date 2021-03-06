// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define FFT_POLY_MOD_INT_CONSTRUCT
#define FFT_POLY_MOD_INT_INV_INLINE
#define MOD_INT_MUL
#define MOD_INT_NEGATE
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/poly/fft_poly_mod_int.h"

// Last include
#include "debug/debug.h"

// g(1)=1
// g(2k+1)=0           k>0
// g(2k)=C(2k-2,k-1)/k k>0
//      =(2k-2)!/(k-1)!/k!
//
// f(n) = sum(f(i) * g(n - i), i from 0 to n-1)
//
// As g(0) = 0,
// f(n) = sum(f(i) * g(n - i), i from 0 to n) for n > 0
// f(0) = 1
//
// F-1=F*G
// F(1-G)=1

const int MAXK2 = (100000 << 1) | 1;
const int MOD = 1000000007;

using ModInt = math::ModInt<int, int64_t, MOD>;
using FFT_T = double;
using FFTPolyModInt = math::FFTPolyModInt<FFT_T, int, int64_t, MOD>;

ModInt facts[MAXK2], invFacts[MAXK2];

int main() {
  math::FFTUtils<FFT_T>::instance().initCapacity(1 << 18);
  int n, k;
  scanf("%d%d", &n, &k);
  int k2 = k << 1;
  facts[0] = 1;
  for (int i = 1; i <= k2; ++i) {
    facts[i] = facts[i - 1] * i;
  }
  invFacts[k2] = facts[k2].inv();
  for (int i = k2 - 1; i >= 0; --i) {
    invFacts[i] = invFacts[i + 1] * (i + 1);
  }
  FFTPolyModInt bases(n + 1, 0);
  bases[0] = 1;
  bases[1] = MOD - 1;
  for (int i = 2; i <= min(n, k << 1); i += 2) {
    bases[i] = -(facts[i - 2] * invFacts[i >> 1] * invFacts[(i >> 1) - 1]);
  }
  bases.invInline();
  printf("%d\n", bases.back()._v);
}
