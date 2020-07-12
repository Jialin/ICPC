#pragma once

#include <functional>

#include "math/prime/miller_rabin32.h"
#include "math/prime/rho32.h"

using namespace std;

namespace math {

inline void
factorize32(uint32_t n, const function<void(uint32_t, int)>& processor) {
  if (!(n & 1)) {
    int shift = __builtin_ctz(n);
    n >>= shift;
    processor(2, shift);
  }
  while (n > 1) {
    if (millerRabin32(n)) {
      processor(n, 1);
      break;
    }
    uint32_t p = n;
    do {
      p = rho32(p);
    } while (p == n || !millerRabin32(p));
    int cnt = 1;
    for (n /= p; !(n % p); n /= p, ++cnt) {}
    processor(p, cnt);
  }
}

} // namespace math
