#pragma once

#include <cmath>

#include "collections/hashmap.h"
#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

namespace math {

// Calculates minimum non-negative x where k*a^x=b (% mod), a and m are coprime
//
// Returns whether x exists
template<typename V = int32_t, typename V_SQR = int64_t>
struct LogModCoPrime {
  inline LogModCoPrime() {}

  inline LogModCoPrime(int hashMapSize, int keyCap = -1) {
    init(hashMapSize, keyCap);
  }

  inline void init(int hashMapSize, int keyCap = -1) {
    _hashMapSize = hashMapSize;
    _keyCap = keyCap;
  }

  inline bool calc(V a, V b, V mod, V& res, V k = 1) {
    DEBUG_TRUE(
        _hashMapSize > 0,
        "We should initialize hashMapSize to positive. Currently, it's %d.\n",
        _hashMapSize);
    fixModInline(a, mod);
    fixModInline(b, mod);
    V n = static_cast<V>(sqrt(mod) + 1);
    _vals.init(_hashMapSize, _keyCap);
    int q = 0;
    for (V cur = b; q <= n; ++q) {
      _vals.set(cur, q, true /* forceEmplaceBack */);
      cur = mulMod<V, V_SQR>(cur, a, mod);
    }
    V an = expMod<V, V, V_SQR>(a, n, mod);
    int p = 1;
    for (V cur = fixMod(k, mod); p <= n; ++p) {
      cur = mulMod<V, V_SQR>(cur, an, mod);
      auto* pos = _vals.getPtr(cur);
      if (pos) {
        res = n * p - *pos;
        return true;
      }
    }
    return false;
  }

  collections::Hashmap<V, int> _vals;
  int _hashMapSize, _keyCap;
};

} // namespace math
