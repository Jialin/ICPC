#pragma once

#include "math/gcd/ext_gcd.h"
#include "math/mod/slight_fix_inline.h"

namespace math {

template<typename V = int32_t>
inline V invMod(V a, const V& mod) {
  V x0, x1, gcd = extGcd(a, mod, x0, x1);
  DEBUG_EQ(gcd, 1);
  slightFixModInline(x0, mod);
  return x0;
}

} // namespace math
