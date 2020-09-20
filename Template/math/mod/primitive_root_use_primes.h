#pragma once

#include <vector>

#include "math/mod/exp.h"
#include "math/prime/factorize_use_primes.h"
#include "math/prime/phi_use_primes.h"

using namespace std;

namespace math {

template<typename T>
struct PrimitiveRootUsePrimes {
  inline PrimitiveRootUsePrimes() {
    _factors.reserve(32);
    processor = [this](T n, int cnt) { _factors.push_back(n); };
  }

  template<typename PRIME>
  inline bool calc(T n, const vector<PRIME>& primes, T& res) {
    if (n == 1 || n == 2 || n == 4) {
      res = n - 1;
      return true;
    }
    if (!(n & 3)) {
      return false;
    }
    bool two = !(n & 1);
    _factors.clear();
    factorizeUsePrimes<T, PRIME>((n & 1) ? n : n >> 1, primes, processor);
    if (_factors.size() > 1) {
      return false;
    }
    T prime = _factors.front();
    T phi = phiUsePrimes<T, PRIME>(n, primes);
    _factors.clear();
    factorizeUsePrimes<T, PRIME>(phi, primes, processor);
    res = 1;
    for (; res < n; ++res) {
      for (int i = 1; i < prime; ++i, ++res) {
        if (res == 1 || (two && !(res & 1))) {
          continue;
        }
        bool valid = true;
        for (T factor : _factors) {
          if (expMod(res, phi / factor, n) == 1) {
            valid = false;
            break;
          }
        }
        if (valid) {
          return true;
        }
      }
    }
    return false;
  }

  vector<T> _factors;
  function<void(T, int)> processor;
};

} // namespace math
