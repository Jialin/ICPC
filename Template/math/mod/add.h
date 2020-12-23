#pragma once

#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int>
inline V addMod(V a, V b, V mod) {
  V res = a;
  res += b;
  slightFixModInline<V>(res, mod);
  return res;
}

} // namespace math
