#pragma once

#include "debug/debug.h"
#include "math/gcd/ext_gcd.h"
#include "math/mod/slight_fix_inline.h"

namespace math {

template<typename V = int>
inline V invMod(V a, V mod) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
  V x0, x1, gcd = extGcd(a, mod, x0, x1);
#pragma clang diagnostic pop
  DEBUG_EQ(gcd, 1);
  slightFixModInline(x0, mod);
  return x0;
}

} // namespace math
