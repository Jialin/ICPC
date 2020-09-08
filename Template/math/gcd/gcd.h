#pragma once

#include "math/bit/ctz.h"

namespace math {

template<typename V>
inline V gcd(V a, V b) {
  if (!a || !b) {
    return a | b;
  }
  int shift = ctz(a | b);
  a >>= ctz(a);
  do {
    b >>= ctz(b);
    if (a > b) {
      swap(a, b);
    }
    b -= a;
  } while (b);
  return a << shift;
}

} // namespace math
