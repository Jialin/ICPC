#pragma once

#include "math/mod/fix.h"
#include "math/mod/mul_inline.h"

namespace math {

template<typename V = int32_t, typename EXP = int32_t, typename V_SQR = int64_t>
inline V expMod(V base, EXP exp, const V& mod) {
  V res = fixMod<V>(1, mod);
  for (; exp > 0; exp >>= 1) {
    if (exp & 1) {
      mulModInline<V, V_SQR>(res, base, mod);
    }
    mulModInline<V, V_SQR>(base, base, mod);
  }
  return res;
}

} // namespace math
