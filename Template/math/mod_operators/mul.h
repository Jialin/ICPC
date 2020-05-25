#pragma once

#include <cstdint>

#include "math/mod_operators/fix_inline.h"

namespace math {

template <typename V = int32_t, typename VV = int64_t>
inline V mulMod(V a, V b, const V &mod) {
  fixModInline(a, mod);
  fixModInline(b, mod);
  if (!a) {
    return 0;
  }
  return b < mod / a ? a * b : static_cast<VV>(a) * b % mod;
}

} // namespace math
