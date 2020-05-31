#pragma once

#include "math/mod_operators/fix_inline.h"

namespace math {

template<typename V = int32_t, typename VV = int32_t>
inline V addMod(const V& a, const V& b, const V& mod) {
  VV res = a;
  fixModInline<VV>(res, mod);
  res += b;
  fixModInline<VV>(res, mod);
  return res;
}

} // namespace math
