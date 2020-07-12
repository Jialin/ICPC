#pragma once

#include <functional>

using namespace std;

#include "math/prime/miller_rabin.h"
#include "math/prime/rho64.h"

namespace math {

inline void
factorize64(uint64_t n, const function<void(uint64_t, int)>& processor) {
  if (!(n & 1)) {
    int shift = __builtin_ctzll(n);
    n >>= shift;
    processor(2, shift);
  }
  while (n > 1) {
    if (millerRabin(n)) {
      processor(n, 1);
      break;
    }
    uint64_t p = n;
    do {
      p = rho64(p);
    } while (p == n || !millerRabin(p));
    int cnt = 1;
    for (n /= p; !(n % p); n /= p, ++cnt) {}
    processor(p, cnt);
  }
}

} // namespace math
