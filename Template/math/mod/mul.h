#pragma once

#include "math/mod/mul_inline_safe.h"

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
inline V mulMod(V a, const V& b, const V& mod) {
  mulModInlineSafe<V, V_SQR>(a, b, mod);
  return a;
}

} // namespace math
