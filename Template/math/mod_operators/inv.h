#pragma once

#include "math/ext_gcd.h"
#include "math/mod_operators/slight_fix_inline.h"

namespace math {

template<typename V = int32_t>
inline V invMod(V a, const V& mod) {
  V x0;
  V x1;
  assert(extGcd(a, mod, x0, x1) == 1);
  slightFixModInline(x0, mod);
  return x0;
}

} // namespace math
