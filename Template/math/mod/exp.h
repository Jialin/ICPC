#pragma once

#include <cassert>

#include "math/mod/fix_inline.h"
#include "math/mod/mul_inline.h"

namespace math {

template<typename V = int32_t, typename EXP = int32_t, typename VV = int64_t>
inline V expMod(V base, EXP exp, const V& mod) {
  assert(exp >= 0);
  fixModInline<V>(base, mod);
  V res = 1;
  fixModInline<V>(res, mod);
  for (; exp > 0; exp >>= 1) {
    if (exp & 1) {
      mulModInline<V, VV>(res, base, mod);
    }
    mulModInline<V, VV>(base, base, mod);
  }
  return res;
}

} // namespace math
