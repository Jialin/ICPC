#pragma once

#include <cassert>

#include "math/mod_operators/fix_inline.h"
#include "math/mod_operators/mul.h"

namespace math {

template <typename V = int32_t, typename EXP = int32_t, typename VV = int64_t>
V expMod(V v, EXP exp, const V &mod) {
  assert(exp >= 0);
  fixModInline(v, mod);
  V res = 1;
  for (; exp > 0; exp >>= 1, v = mulMod(v, v, mod)) {
    if (exp & 1) {
      res = mulMod<V, VV>(res, v, mod);
    }
  }
  return res;
}

} // namespace math
