#pragma once

#include <functional>

using namespace std;

#include "math/prime/miller_rabin128.h"
#include "math/prime/rho128.h"

namespace math {

MontgomeryMul mont;

inline void
factorize128(__uint128_t n, const function<bool(__uint128_t, int)>& processor) {
  if (!(n & 1)) {
    int shift = ctz128(n);
    n >>= shift;
    if (!processor(2, shift)) {
      return;
    }
  }
  while (n > 1) {
    mont.init(n);
    if (millerRabin128(n, mont, false)) {
      if (!processor(n, 1)) {
        return;
      }
      break;
    }
    __uint128_t p = n;
    do {
      mont.init(p);
      p = rho128(p, mont, false);
    } while (p == n || !millerRabin128(p, mont, false));
    int cnt = 1;
    for (n /= p; !(n % p); n /= p, ++cnt) {}
    if (!processor(p, cnt)) {
      return;
    }
  }
}

} // namespace math
