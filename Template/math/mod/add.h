#pragma once

#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int32_t, typename V_DOUBLE = int32_t>
inline V addMod(const V& a, V b, const V& mod) {
  V_DOUBLE res = a;
  fixModInline<V_DOUBLE>(res, mod);
  fixModInline<V>(b, mod);
  res += b;
  slightFixModInline<V_DOUBLE>(res, mod);
  return res;
}

} // namespace math
