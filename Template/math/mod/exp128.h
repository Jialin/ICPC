#pragma once

#include "math/montgomery_mul.h"

namespace math {

template<typename EXP = __uint128_t>
inline __uint128_t
exp128(const MontgomeryMul& mont, __uint128_t base, EXP exp) {
  __uint128_t res = mont.one;
  for (; exp > 0; exp >>= 1) {
    if (exp & 1) {
      res = mont.mul(res, base);
    }
    base = mont.mul(base, base);
  }
  return res;
}

} // namespace math
