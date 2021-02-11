// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define FFT_POLY_MOD_INT_RECURRENCE
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/poly/fft_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000007;

using Poly = math::FFTPolyModInt<double, int, int64_t, MOD>;

Poly coefs, xs;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  coefs.resize(n);
  xs.resize(n);
  FOR(i, 0, n) {
    coefs[i] = 1;
    xs[i] = 1;
  }
  printf("%d\n", coefs.recurrence(xs, k - 1)._v);
}
