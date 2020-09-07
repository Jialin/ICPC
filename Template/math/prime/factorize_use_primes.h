#pragma once

#include <functional>
#include <vector>

#include "debug/debug.h"
#include "math/bit/ctz.h"

using namespace std;

namespace math {

template<typename T, typename PRIME>
inline void factorizeUsePrimes(
    T n,
    const vector<PRIME>& primes,
    const function<void(PRIME, int)>& processor) {
  DEBUG_TRUE(
      primes.back() >= n / primes.back(),
      "Square of largest prime (%lu) should larger than %lu\n",
      primes.back(),
      n);
  if (!(n & 1)) {
    int shift = ctz<T>(n);
    n >>= shift;
    processor(2, shift);
  }
  for (int i = 1; primes[i] <= n / primes[i]; ++i) {
    if (n % primes[i]) {
      continue;
    }
    n /= primes[i];
    int cnt = 1;
    for (; !(n % primes[i]); n /= primes[i], ++cnt) {}
    processor(primes[i], cnt);
  }
  if (n > 1) {
    processor(n, 1);
  }
}

} // namespace math
