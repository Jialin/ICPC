#pragma once

#include <cmath>

#include "collections/hashmap.h"
#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/inv.h"
#include "math/mod/mul.h"

//////////////////////////////////////////////////////////////////////////////
// #include "math/mod/log_coprime.h"
//
// logMod = math::LogModCoPrime();
// logMod.init(100003);
// res = logMod.calc(base, remainder, mod, exist);
//
// logMod = math::LogModCoPrime(hashMapSize, keyCap);
// res = logMod.calc(base, remainder, mod, exist);
//
// logMod = math::LogModCoPrime(hashMapSize, keyCap);
// logMod.precomputeFixedBaseMod(base, mod, static_cast<int>(sqrt(mod) + 1));
// res = logMod.calcFixedBaseMod(remainder, exist);
//////////////////////////////////////////////////////////////////////////////
namespace math {

// Calculates minimum non-negative x where
//   k*base^x=remainder (% mod), base and mod are coprime
//
// The bool reference indicates whether the root exists
template<typename V = int32_t, typename V_SQR = int64_t>
struct LogModCoPrime {
  inline LogModCoPrime() {}

  inline LogModCoPrime(
      int hashMapSize, bool positiveResultOnly = false, int keyCap = -1) {
    init(hashMapSize, positiveResultOnly, keyCap);
  }

  inline void
  init(int hashMapSize, bool positiveResultOnly = false, int keyCap = -1) {
    _hashMapSize = hashMapSize;
    _positiveResultOnly = positiveResultOnly;
    _keyCap = keyCap;
  }

  inline void precomputeFixedBaseMod(V base, V mod, int step, V k = 1) {
    _mod = mod;
    _step = step;
    _maxStepCnt = _mod / _step + 5;
    DEBUG_TRUE(
        _hashMapSize > 0,
        "We should initialize hashMapSize to positive. Currently, it's %d.\n",
        _hashMapSize);
    fixModInline(base, mod);
    _invBase = invMod<V>(base, mod);
    _invBasePowStep = expMod<V, V, V_SQR>(_invBase, step, mod);
    _vals.init(_hashMapSize, _keyCap);
    V cur = fixMod<V>(k, mod);
    int totalStep = _step + !_positiveResultOnly;
    for (int q = 0; q < totalStep; ++q) {
      _vals.set(cur, q, true /* forceEmplaceBack */);
      cur = mulMod<V, V_SQR>(cur, _invBase, mod);
    }
  }

  inline V calcFixedBaseMod(V remainder, bool& exist) {
    exist = false;
    fixModInline(remainder, _mod);
    V cur = remainder;
    for (int p = 1; p <= _maxStepCnt; ++p) {
      cur = mulMod<V, V_SQR>(cur, _invBasePowStep, _mod);
      auto* pos = _vals.getPtr(cur);
      if (pos) {
        exist = true;
        return _step * p - *pos;
      }
    }
    return 0;
  }

  inline V calc(V base, V remainder, V mod, bool& exist, V k = 1) {
    precomputeFixedBaseMod(base, mod, static_cast<int>(sqrt(mod) + 1), k);
    return calcFixedBaseMod(remainder, exist);
  }

  collections::Hashmap<V, int> _vals;
  int _hashMapSize, _keyCap, _step, _maxStepCnt;
  bool _positiveResultOnly;
  V _invBase, _invBasePowStep, _mod;
};

} // namespace math
