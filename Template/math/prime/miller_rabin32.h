#pragma once

#include "math/mod/exp_safe.h"

using namespace std;

namespace math {

namespace {

inline bool checkComposite32(uint32_t n, uint32_t a, uint32_t d, int s) {
  uint32_t x = expModSafe<uint32_t, uint32_t, uint64_t>(a, d, n);
  if (x == 1 || x == n - 1) {
    return false;
  }
  for (int i = 1; i < s; ++i) {
    mulModInline<uint32_t, uint64_t>(x, x, n);
    if (x == n - 1) {
      return false;
    }
  }
  return true;
}

} // namespace

inline bool millerRabin32(uint32_t n) {
  if (n < 2) {
    return false;
  }
  if (n == 2 || n == 7 || n == 61) {
    return true;
  }
  uint32_t n1 = n - 1;
  int ctz = __builtin_ctz(n1);
  n1 >>= ctz;
  return !checkComposite32(n, 2, n1, ctz) && !checkComposite32(n, 7, n1, ctz) &&
         !checkComposite32(n, 61, n1, ctz);
}

} // namespace math
