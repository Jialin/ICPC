#pragma once

#include "math/mod/exp_safe.h"

using namespace std;

namespace math {

namespace {

inline bool checkComposite64(uint64_t n, uint64_t a, uint64_t d, int s) {
  uint64_t x = expModSafe<uint64_t, uint64_t, __uint128_t>(a, d, n);
  if (x == 1 || x == n - 1) {
    return false;
  }
  for (int i = 1; i < s; ++i) {
    mulModInlineSafe<uint64_t, __uint128_t>(x, x, n);
    if (x == n - 1) {
      return false;
    }
  }
  return true;
}

} // namespace

inline bool millerRabin64(uint64_t n) {
  if (n < 2) {
    return false;
  }
  if (n == 2 || n == 3 || n == 5 || n == 13 || n == 19 || n == 73 || n == 193 ||
      n == 407521 || n == 299210837) {
    return true;
  }
  uint64_t n1 = n - 1;
  int ctz = __builtin_ctzll(n1);
  n1 >>= ctz;
  return !checkComposite64(n, 2, n1, ctz) &&
         !checkComposite64(n, 325, n1, ctz) &&
         !checkComposite64(n, 9375, n1, ctz) &&
         !checkComposite64(n, 28178, n1, ctz) &&
         !checkComposite64(n, 450775, n1, ctz) &&
         !checkComposite64(n, 9780504, n1, ctz) &&
         !checkComposite64(n, 1795265022, n1, ctz);
}

} // namespace math
