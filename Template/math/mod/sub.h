#pragma once

#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int>
inline V subMod(const V& a, V b, const V& mod) {
  V res = a;
  fixModInline<V>(res, mod);
  fixModInline<V>(b, mod);
  if (res >= b) {
    res -= b;
  } else {
    res = mod - (b - res);
  }
  slightFixModInline<V>(res, mod);
  return res;
}

} // namespace math
