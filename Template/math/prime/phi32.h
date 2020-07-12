#pragma once

#include <vector>

#include "math/prime/prime_iterator.h"

using namespace std;

namespace math {

// Provides all primes less than sqrt(n)
uint32_t phi32(uint32_t n, const vector<uint32_t>& primes) {
  uint32_t res = n;
  for (uint32_t prime : primes) {
    if (prime > n / prime) {
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
