#pragma once

#include <vector>

#include "math/prime/prime_iterator.h"

using namespace std;

namespace math {

class PrimeGenerator {
public:
  inline PrimeGenerator(int n, int capacity = -1) {
    init(n, capacity);
  }

  inline void init(int n, int capacity = -1) {
    pi.init(n);
    primes.clear();
    if (capacity >= 0) {
      primes.reserve(capacity);
    }
    pi.iterate(n, [this](uint32_t prime) {
      primes.push_back(prime);
      return true;
    });
    DEBUGF_TRUE(
        primes.size() >= capacity,
        "Set primes capacity? primes.size():%lu capacity:%d\n",
        primes.size(),
        capacity);
  }

  vector<int> primes;

private:
  PrimeIterator pi;
};

} // namespace math
