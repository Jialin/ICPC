
#pragma once

#include "math/mod/mul_inline.h"

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
inline V mulMod(V a, V b, V mod) {
  mulModInline<V, V_SQR>(a, b, mod);
  return a;
}

} // namespace math
