#pragma once

#include "math/mod_operators/fix_inline.h"

namespace math {

template <typename V = int32_t, typename VV = int64_t>
inline void mulModInline(V &res, V x, const V &mod) {
  fixModInline<V>(res, mod);
  fixModInline<V>(x, mod);
  if (!res || !x) {
    res = 0;
  } else if (res < mod / x) {
    res *= x;
  } else {
    res = static_cast<VV>(res) * x % mod;
  }
}

} // namespace math
