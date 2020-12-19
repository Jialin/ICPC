#pragma once

#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int32_t>
inline V fixMod(V v, V mod) {
  V res = v;
  fixModInline<V>(res, mod);
  return res;
}

} // namespace math
