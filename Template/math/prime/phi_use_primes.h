#pragma once

#include <vector>

#include "debug/debug.h"

using namespace std;

namespace math {

template<typename T, typename PRIME>
inline T phiUsePrimes(T n, const vector<PRIME>& primes) {
  DEBUGF_TRUE(
      primes.back() >= n / primes.back(),
      "Square of largest prime (%d) should larger than %lld",
      primes.back(),
      static_cast<int64_t>(n));
  T res = n;
  for (PRIME prime : primes) {
    if (static_cast<T>(prime) > n / prime) {
      break;
    }
    if (n % prime) {
      continue;
    }
    res -= res / prime;
    for (n /= prime; !(n % prime); n /= prime) {}
  }
  if (n > 1) {
    res -= res / n;
  }
  return res;
}

} // namespace math
