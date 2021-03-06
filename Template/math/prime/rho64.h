#pragma once

#include <algorithm>

#include "math/gcd/gcd64.h"
#include "math/mod/fix.h"
#include "math/mod/mul_inline.h"

using namespace std;

namespace math {

namespace {

const int RHO_STEP_64 = 128;

inline uint64_t rhoF64(uint64_t x, uint64_t c, uint64_t mod) {
  mulModInline<uint64_t, __uint128_t>(x, x, mod);
  return fixMod(x + c, mod);
}

} // namespace

inline uint64_t rho64(uint64_t n, uint64_t x = 0, uint64_t c = 0) {
  if (!(n & 1)) {
    return 2;
  }
  if (!x) {
    x = fixMod<uint64_t>(rand(), n);
  }
  if (!c) {
    c = fixMod<uint64_t>(rand(), n);
  }
  uint64_t g = 1, q = fixMod<uint64_t>(1, n), xs = 0, y = 0;
  for (int l = 1; g == 1; l <<= 1) {
    y = x;
    for (int i = 1; i < l; ++i) {
      x = rhoF64(x, c, n);
    }
    for (int k = 0; k < l && g == 1; k += RHO_STEP_64) {
      xs = x;
      for (int i = min(l - k, RHO_STEP_64); i > 0; --i) {
        x = rhoF64(x, c, n);
        mulModInline<uint64_t, __uint128_t>(q, y > x ? y - x : x - y, n);
      }
      g = gcd64(q, n);
    }
  }
  if (g == n) {
    do {
      xs = rhoF64(xs, c, n);
      g = gcd64(xs > y ? xs - y : y - xs, n);
    } while (g == 1);
  }
  return g;
}

} // namespace math
