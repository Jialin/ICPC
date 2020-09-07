#pragma once

#include <vector>

#include "debug/debug.h"
#include "math/chinese_remainder.h"
#include "math/combination/combination_prime.h"
#include "math/prime/factorize_use_primes.h"

using namespace std;

namespace math {

// Computes C(a, b) % <mod>
template<
    typename MOD = int32_t,
    typename MOD_SQR = int64_t,
    typename MOD_DOUBLE = MOD>
struct CombinationModFull {
  inline CombinationModFull() {}

  inline CombinationModFull(int n, MOD mod, const vector<int>& primes) {
    init(n, mod, primes);
  }

  inline void init(int n, MOD mod, const vector<int>& primes) {
    _combs.reserve(10);
    _combs.clear();
    factorizeUsePrimes<MOD, int>(mod, primes, [this, n](MOD prime, int cnt) {
      _combs.emplace_back(n, prime, cnt);
    });
  }

  inline MOD calc(int n, int m) const {
    if (n < m) {
      return 0;
    }
    MOD res = 0, resMod = 1;
    for (const auto& comb : _combs) {
      chineseRemainder<MOD, MOD_SQR, MOD_DOUBLE>(
          res, resMod, comb.calc(n, m), comb._mod, res, resMod);
    }
    return res;
  }

  vector<CombinationModPrime<MOD, MOD_SQR>> _combs;
};

} // namespace math
