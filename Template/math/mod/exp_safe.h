#pragma once

#include <cassert>

#include "math/mod/fix_inline.h"
#include "math/mod/mul_inline_safe.h"

namespace math {

template<typename V = int32_t, typename EXP = int32_t, typename V_SQR = int64_t>
inline V expModSafe(V base, EXP exp, const V& mod) {
  assert(exp >= 0);
  fixModInline<V>(base, mod);
  V res = 1;
  fixModInline<V>(res, mod);
  for (; exp > 0; exp >>= 1) {
    if (exp & 1) {
      mulModInlineSafe<V, V_SQR>(res, base, mod);
    }
    mulModInlineSafe<V, V_SQR>(base, base, mod);
  }
  return res;
}

} // namespace math
