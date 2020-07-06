#pragma once

#include <algorithm>

using namespace std;

#include "math/gcd128.h"
#include "math/mod/add.h"
#include "math/montgomery_mul.h"

namespace math {

namespace {

const int RHO_STEP_128 = 128;

inline __uint128_t
rhoF128(const MontgomeryMul& mont, __uint128_t x, __uint128_t c) {
  return addMod(mont.mul(x, x), c, mont.mod);
}

} // namespace

inline __uint128_t rho128(
    __uint128_t n,
    MontgomeryMul& mont,
    bool initMont = true,
    __uint128_t x = 0,
    __uint128_t c = 0) {
  if (!(n & 1)) {
    return 2;
  }
  if (initMont) {
    mont.init(n);
  }
  if (!x) {
    x = mont.convert(rand());
  }
  if (!c) {
    c = mont.convert(rand());
  }
  __uint128_t g = 1, q = 1, xs = 0, y = 0;
  for (int l = 1; g == 1; l <<= 1) {
    y = x;
    for (int i = 1; i < l; ++i) {
      x = rhoF128(mont, x, c);
    }
    for (int k = 0; k < l && g == 1; k += RHO_STEP_128) {
      xs = x;
      for (int i = min(l - k, RHO_STEP_128); i > 0; --i) {
        x = rhoF128(mont, x, c);
        q = mont.mul(q, y > x ? y - x : x - y);
      }
      g = gcd128(q, n);
    }
  }
  if (g == n) {
    do {
      xs = rhoF128(mont, xs, c);
      g = gcd128(xs > y ? xs - y : y - xs, n);
    } while (g == 1);
  }
  return g;
}

} // namespace math
