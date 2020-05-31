#pragma once

#include "math/mod_operators/fix_inline.h"

namespace math {

template<typename V = int32_t, typename VV = int32_t>
inline void addModInline(V& a, V b, const V& mod) {
  fixModInline(a, mod);
  fixModInline(b, mod);
  a += b;
  slightFixModInline(a, mod);
}

} // namespace math
