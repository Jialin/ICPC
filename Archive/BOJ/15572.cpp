// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define FFT_POLY_MOD_INT_RECURRENCE
#define MOD_INT_ADD
#define MOD_INT_SUB
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/poly/fft_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1999;

using Poly = math::FFTPolyModInt<double, int, int64_t, MOD>;

Poly coefs, vs, two;

int main() {
  int n;
  int64_t m;
  scanf("%d%lld", &n, &m);
  two.resize(n + 1);
  two[0] = 1;
  for (int i = 1; i <= n; ++i) {
    two[i] = two[i - 1] + two[i - 1];
  }
  vs.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    vs[i] = two[i];
  }
  vs[n - 1] = two[n] - 1;
  coefs.assign(n, 1);
  coefs[0] = two[n - 1];
  printf("%d\n", coefs.recurrence(vs, m - 1)._v);
}
