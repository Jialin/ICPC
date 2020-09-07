#pragma once

#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int32_t>
inline V addMod(const V& a, V b, const V& mod) {
  V res = a;
  fixModInline<V>(res, mod);
  fixModInline<V>(b, mod);
  res += b;
  slightFixModInline<V>(res, mod);
  return res;
}

} // namespace math
