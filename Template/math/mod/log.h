#pragma once

#include "math/gcd/gcd.h"
#include "math/mod/log_coprime.h"

namespace math {

// Calculates minimum non-negative x where a^x=b (% mod)
//
// The bool reference indicates whether the log exists
template<typename V = int32_t, typename V_SQR = int64_t>
struct LogMod {
  inline LogMod(int hashMapSize, int keyCap = -1) {
    init(hashMapSize, keyCap);
  }

  inline void init(int hashMapSize, int keyCap = -1) {
    _logMod.init(hashMapSize, keyCap);
  }

  inline V calc(V a, V b, V mod, bool& exist) {
    exist = false;
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
        exist = true;
        return delta;
      }
      if (b % g) {
        return 0;
      }
      b /= g;
      mod /= g;
      ++delta;
      k = mulMod<V, V_SQR>(fixMod(k, mod), fixMod(a / g, mod), mod);
    }
    V res = _logMod.calc(a, b, mod, exist, k);
    return exist ? res + delta : 0;
  }

  LogModCoPrime<V, V_SQR> _logMod;
};

} // namespace math
