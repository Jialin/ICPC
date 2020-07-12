#pragma once

#include <functional>

#include "math/prime/miller_rabin64.h"
#include "math/prime/rho64.h"

using namespace std;

namespace math {

inline void
factorize64(uint64_t n, const function<void(uint64_t, int)>& processor) {
  if (!(n & 1)) {
    int shift = __builtin_ctzll(n);
    n >>= shift;
    processor(2, shift);
  }
  while (n > 1) {
    if (millerRabin64(n)) {
      processor(n, 1);
      break;
    }
    uint64_t p = n;
    do {
      p = rho64(p);
    } while (p == n || !millerRabin64(p));
    int cnt = 1;
    for (n /= p; !(n % p); n /= p, ++cnt) {}
    processor(p, cnt);
  }
}

} // namespace math
