#pragma once

#include "collections/bitset.h"

using namespace std;

namespace math {

inline void markPrimes(int n, vector<bool>& isPrime) {
  isPrime.assign(n + 1, true);
  isPrime[0] = false;
  isPrime[1] = false;
  for (int i = 2; i <= n / i; ++i) {
    if (!isPrime[i]) {
      continue;
    }
    int ii = (i & 1) ? i << 1 : i;
    for (int j = i * i; j <= n; j += ii) {
      isPrime[j] = false;
    }
  }
}

} // namespace math
