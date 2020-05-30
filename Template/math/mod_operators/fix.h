#pragma once

#include "math/mod_operators/fix_inline.h"

namespace math {

template <typename V = int32_t> inline V fixMod(const V &v, const V &mod) {
  V res = v;
  fixModInline(res, mod);
  return res;
}

} // namespace math
