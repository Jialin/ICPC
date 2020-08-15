#pragma once

#include <vector>

using namespace std;

namespace math {

// Need to provide all primes less than sqrt(n)
uint32_t phi32(uint32_t n, const vector<int>& primes) {
  uint32_t res = n;
  for (int prime : primes) {
    if (prime > static_cast<int>(n / prime)) {
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
