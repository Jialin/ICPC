// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define NTT_POLY_MOD_INT_RECURRENCE
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "io/read_int.h"
#include "math/poly/ntt_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int PRIME = 104857601;
const int ROOT = 21;

using Poly = math::NTTPolyModInt<int, int64_t, PRIME, ROOT>;

Poly coefs, xs;

int main() {
  int n;
  int64_t k;
  while (io::readInt(n)) {
    math::NTTUtils<int, int64_t, PRIME, ROOT>::instance().initCapacity((n + 1) << 1);
    io::readInt(k);
    xs.resize(n);
    FOR(i, 0, n) {
      int v;
      io::readInt(v);
      xs[i] = v;
    }
    coefs.resize(n);
    for (int i = n - 1; i >= 0; --i) {
      int v;
      io::readInt(v);
      coefs[i] = v;
    }
    printf("%d\n", coefs.recurrence(xs, k - 1)._v);
  }
}
