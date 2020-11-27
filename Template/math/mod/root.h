#pragma once

#include "math/mod/exp.h"
#include "math/mod/log_coprime.h"

namespace math {

// Calculates x where x^exp=remainder (% mod)
//
// The bool reference indicates whether the root exists
template<typename V = int32_t, typename V_SQR = int64_t>
inline V rootMod(
    V exp,
    V remainder,
    V mod,
    V primitiveRoot,
    LogModCoPrime<V, V_SQR>& logMod,
    bool& exist) {
  fixModInline<V>(remainder, mod);
  if (!remainder) {
    exist = true;
    return 0;
  }
  V res = logMod.calc(
      expMod<V, V_SQR>(primitiveRoot, exp, mod), remainder, mod, exist);
  return exist ? expMod<V, V_SQR>(primitiveRoot, res, mod) : false;
}

} // namespace math
