#pragma once

#include "math/mod/slight_fix_inline.h"

namespace math {

template<typename V = int>
inline V subMod(V a, V b, V mod) {
  V res = a;
  if (res >= b) {
    res -= b;
  } else {
    res = mod - (b - res);
  }
  slightFixModInline<V>(res, mod);
  return res;
}

} // namespace math
