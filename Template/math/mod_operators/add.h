#pragma once

#include <cassert>

#include "math/mod_operators/fix_inline.h"

namespace math {

template <typename V = int32_t, typename VV = int32_t>
inline V addMod(V a, V b, const V &mod) {
  VV res = a;
  res += b;
  fixModInline(res, static_cast<VV>(mod));
  return res;
}

} // namespace math
