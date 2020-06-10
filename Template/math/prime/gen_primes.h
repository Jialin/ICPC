#pragma once

#include <algorithm>
#include <vector>

using namespace std;

namespace math {

inline void genPrimes(int n, vector<int>& primes, vector<int>& smallestPrime) {
  primes.clear();
  smallestPrime.assign(n + 1, -1);
  for (int i = 2; i <= n; ++i) {
    if (smallestPrime[i] < 0) {
      smallestPrime[i] = i;
      primes.push_back(i);
    }
    int bound = min(smallestPrime[i], n / i);
    for (size_t j = 0; j < primes.size() && primes[j] <= bound; ++j) {
      smallestPrime[i * primes[j]] = primes[j];
    }
  }
}

} // namespace math
