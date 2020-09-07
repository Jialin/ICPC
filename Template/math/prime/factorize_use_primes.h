#pragma once

#include <functional>
#include <vector>

#include "debug/debug.h"

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
  for (PRIME prime : primes) {
    if (prime > n / prime) {
      break;
    }
    if (n % prime) {
      continue;
    }
    n /= prime;
    int cnt = 1;
    for (; !(n % prime); n /= prime, ++cnt) {}
    processor(prime, cnt);
  }
  if (n > 1) {
    processor(n, 1);
  }
}

} // namespace math
