#pragma once

#include <functional>

using namespace std;

#include "math/prime/miller_rabin128.h"
#include "math/prime/rho128.h"

namespace math {

inline void factorize128(
    __uint128_t n,
    MontgomeryMul& mont,
    MontgomeryMul& mont2,
    const function<void(__uint128_t, int)>& processor) {
  if (!(n & 1)) {
    int shift = ctz128(n);
    n >>= shift;
    processor(2, shift);
  }
  while (n > 1) {
    mont.init(n);
    if (millerRabin128(n, mont, false)) {
      processor(n, 1);
      break;
    }
    __uint128_t p = n;
    mont.init(p);
    do {
      p = rho128(p, mont, false);
    } while (p == n || !millerRabin128(p, mont2));
    int cnt = 1;
    for (n /= p; !(n % p); n /= p, ++cnt) {}
    processor(p, cnt);
  }
}

} // namespace math
