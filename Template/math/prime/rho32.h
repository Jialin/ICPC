#pragma once

#include <algorithm>

#include "math/gcd32.h"
#include "math/mod/add.h"
#include "math/mod/mul_inline.h"

using namespace std;

namespace math {

namespace {

const int RHO_STEP_32 = 128;

inline uint32_t rhoF32(uint32_t x, uint32_t c, uint32_t mod) {
  mulModInline<uint32_t, uint64_t>(x, x, mod);
  return addMod(x, c, mod);
}

} // namespace

inline uint32_t rho32(uint32_t n, uint32_t x = 0, uint32_t c = 0) {
  if (!(n & 1)) {
    return 2;
  }
  if (!x) {
    x = rand();
  }
  if (!c) {
    c = rand();
  }
  uint32_t g = 1, q = 1, xs = 0, y = 0;
  for (int l = 1; g == 1; l <<= 1) {
    y = x;
    for (int i = 1; i < l; ++i) {
      x = rhoF32(x, c, n);
    }
    for (int k = 0; k < l && g == 1; k += RHO_STEP_32) {
      xs = x;
      for (int i = min(l - k, RHO_STEP_32); i > 0; --i) {
        x = rhoF32(x, c, n);
        mulModInline<uint32_t, uint64_t>(q, y > x ? y - x : x - y, n);
      }
      g = gcd32(q, n);
    }
  }
  if (g == n) {
    do {
      xs = rhoF32(xs, c, n);
      g = gcd32(xs > y ? xs - y : y - xs, n);
    } while (g == 1);
  }
  return g;
}

} // namespace math
