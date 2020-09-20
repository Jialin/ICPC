#pragma once

#include <vector>

#include "math/mod/exp.h"
#include "math/prime/factorize_use_primes.h"

using namespace std;

namespace math {

template<typename T>
struct PrimitiveRootPrimeUsePrimes {
  inline PrimitiveRootPrimeUsePrimes() {
    _factors.reserve(32);
    processor = [this](T n, int cnt) { _factors.push_back(n); };
  }

  template<typename PRIME>
  inline bool calc(T n, const vector<PRIME>& primes, T& res) {
    if (n == 2) {
      res = n - 1;
      return true;
    }
    T phi = n - 1;
    _factors.clear();
    factorizeUsePrimes<T, PRIME>(phi, primes, processor);
    for (res = 2; res < n; ++res) {
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
    return false;
  }

  vector<T> _factors;
  function<void(T, int)> processor;
};

} // namespace math
