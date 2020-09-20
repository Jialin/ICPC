#pragma once

#include <vector>

#include "debug/debug.h"
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
  inline T calc(T n, const vector<PRIME>& primes) {
    if (n == 2) {
      return 1;
    }
    T phi = n - 1;
    _factors.clear();
    factorizeUsePrimes<T, PRIME>(phi, primes, processor);
    for (T res = 2; res < n; ++res) {
      bool valid = true;
      for (T factor : _factors) {
        if (expMod(res, phi / factor, n) == 1) {
          valid = false;
          break;
        }
      }
      if (valid) {
        return res;
      }
    }
    DEBUG(
        "We should never hit here, all primes should have primitive root. "
        "n:%d\n",
        n);
    return 0;
  }

  vector<T> _factors;
  function<void(T, int)> processor;
};

} // namespace math
