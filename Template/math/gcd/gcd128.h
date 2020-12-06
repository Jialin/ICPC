#pragma once

#include <algorithm>

#include "math/bit/ctz128.h"

using namespace std;

namespace math {

inline __uint128_t gcd128(__uint128_t a, __uint128_t b) {
  if (!a || !b) {
    return a | b;
  }
  auto shift = ctz128(a | b);
  a >>= ctz128(a);
  do {
    b >>= ctz128(b);
    if (a > b) {
      swap(a, b);
    }
    b -= a;
  } while (b);
  return a << shift;
}

} // namespace math
