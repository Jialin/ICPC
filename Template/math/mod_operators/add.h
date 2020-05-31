#pragma once

#include "math/mod_operators/add_inline.h"

namespace math {

template<typename V = int32_t, typename VV = int32_t>
inline V addMod(V a, const V& b, const V& mod) {
  addModInline(a, b, mod);
  return a;
}

} // namespace math
