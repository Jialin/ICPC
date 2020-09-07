#pragma once

#include <vector>

#include "debug/debug.h"
#include "math/chinese_remainder.h"
#include "math/combination/combination_prime.h"
#include "math/prime/factorize_use_primes.h"

using namespace std;

namespace math {

// Computes C(a, b) % <mod>
struct CombinationModFull {
  inline CombinationModFull() {}

  inline CombinationModFull(int n, int mod, const vector<int>& primes) {
    init(n, mod, primes);
  }

  inline void init(int n, int mod, const vector<int>& primes) {
    _combs.reserve(10);
    _combs.clear();
    factorizeUsePrimes<int, int>(mod, primes, [this, n](int prime, int cnt) {
      _combs.emplace_back(n, prime, cnt);
    });
  }

  inline int calc(int n, int m) const {
    if (n < m) {
      return 0;
    }
    int res = 0, resMod = 1;
    for (const auto& comb : _combs) {
      chineseRemainder(res, resMod, comb.calc(n, m), comb._mod, res, resMod);
    }
    return res;
  }

  vector<CombinationModPrime> _combs;
};

} // namespace math
