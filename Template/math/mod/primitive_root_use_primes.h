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
  inline T calc(T n, const vector<PRIME>& primes, bool& exist) {
    exist = false;
    if (n == 1 || n == 2 || n == 4) {
      exist = true;
      return n - 1;
    }
    if (!(n & 3)) {
      return 0;
    }
    bool two = !(n & 1);
    _factors.clear();
    factorizeUsePrimes<T, PRIME>((n & 1) ? n : n >> 1, primes, processor);
    if (_factors.size() > 1) {
      return 0;
    }
    T prime = _factors.front();
    T phi = phiUsePrimes<T, PRIME>(n, primes);
    _factors.clear();
    factorizeUsePrimes<T, PRIME>(phi, primes, processor);
    for (T res = 1; res < n; ++res) {
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
          exist = true;
          return res;
        }
      }
    }
    return 0;
  }

  vector<T> _factors;
  function<void(T, int)> processor;
};

} // namespace math
