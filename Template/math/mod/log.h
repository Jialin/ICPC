#pragma once

#include "math/gcd/gcd.h"
#include "math/mod/log_coprime.h"

////////////////////////////////////////////////////
// #include "math/mod/log.h"
//
// logMod = math::LogMod();
// logMod.init(100003);
// res = logMod.calc(base, remainder, mod, exist);
///////////////////////////////////////////////////
namespace math {

// Calculates minimum non-negative x where base^x=remainder (% mod)
//
// The bool reference indicates whether the log exists
template<typename V = int32_t, typename V_SQR = int64_t>
struct LogMod {
  inline LogMod(
      int hashMapSize, bool positiveResultOnly = false, int keyCap = -1) {
    init(hashMapSize, positiveResultOnly, keyCap);
  }

  inline void
  init(int hashMapSize, bool positiveResultOnly = false, int keyCap = -1) {
    _logMod.init(hashMapSize, positiveResultOnly, keyCap);
  }

  inline V calc(V base, V remainder, V mod, bool& exist) {
    exist = false;
    fixModInline(base, mod);
    fixModInline(remainder, mod);
    V k = fixMod(1, mod);
    int delta = 0;
    while (true) {
      int g = gcd(base, mod);
      if (g == 1) {
        break;
      }
      if (remainder == k) {
        exist = true;
        return delta;
      }
      if (remainder % g) {
        return 0;
      }
      remainder /= g;
      mod /= g;
      ++delta;
      k = mulMod<V, V_SQR>(fixMod(k, mod), fixMod(base / g, mod), mod);
    }
    V res = _logMod.calc(base, remainder, mod, exist, k);
    return exist ? res + delta : 0;
  }

  LogModCoPrime<V, V_SQR> _logMod;
};

} // namespace math
