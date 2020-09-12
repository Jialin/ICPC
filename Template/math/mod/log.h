#pragma once

#include "math/gcd/gcd.h"
#include "math/mod/log_coprime.h"

namespace math {

// Calculates minimum non-negative x where a^x=b (% mod)
//
// Returns whether x exists
template<typename V = int32_t, typename V_SQR = int64_t>
struct LogMod {
  inline LogMod(int hashMapSize, int keyCap = -1) {
    init(hashMapSize, keyCap);
  }

  inline void init(int hashMapSize, int keyCap = -1) {
    _logMod.init(hashMapSize, keyCap);
  }

  inline bool calc(V a, V b, V mod, V& res) {
    fixModInline(a, mod);
    fixModInline(b, mod);
    V k = fixMod(1, mod);
    int delta = 0;
    while (true) {
      int g = gcd(a, mod);
      if (g == 1) {
        break;
      }
      if (b == k) {
        res = delta;
        return true;
      }
      if (b % g) {
        return false;
      }
      b /= g;
      mod /= g;
      ++delta;
      k = mulMod<V, V_SQR>(fixMod(k, mod), fixMod(a / g, mod), mod);
    }
    if (_logMod.calc(a, b, mod, res, k)) {
      res += delta;
      return true;
    }
    return false;
  }

  LogModCoPrime<V, V_SQR> _logMod;
};

} // namespace math
