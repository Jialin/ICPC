#pragma once

#include "math/mod/mul_inline.h"

namespace math {

template<typename V = int32_t, typename VV = int64_t>
inline V mulMod(V a, const V& b, const V& mod) {
  mulModInline<V, VV>(a, b, mod);
  return a;
}

} // namespace math
