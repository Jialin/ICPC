#pragma once

#include "debug/debug.h"
#include "math/mod/add.h"
#include "math/mod/fix.h"

using namespace std;

namespace math {

template<typename V = int64_t>
struct AccumulatorMod {
  inline AccumulatorMod() {}

  inline AccumulatorMod(V mod) {
    init(mod);
  }

  inline void init(V mod) {
    _mod = mod;
    reset(0);
    _remainder = _invV % mod;
  }

  inline void reset(V v) {
    _invV = numeric_limits<V>::max() - v;
  }

  inline void add(V delta) {
    DEBUG_TRUE(delta >= 0, "{} should be non-negative", delta);
    if (_invV >= delta) {
      _invV -= delta;
    } else {
      _invV = numeric_limits<V>::max() -
              addMod<V>(_remainder, fixMod<V>(delta - _invV, _mod), _mod);
    }
  }

  inline V get() {
    return fixMod<V>(numeric_limits<V>::max() - _invV, _mod);
  }

  V _mod, _remainder, _invV;
};

} // namespace math