#pragma once

#include "debug/debug_basic.h"

using namespace std;

namespace math {

// ax+by=gcd(a, b) and the return
// - value is non-negative
// - x, y satisfy:
//   - abs(x)+abs(y) is minimum, if multiple minimum solutions, x <= y
//
// NOTE: DO NOT use unsigned type
template<typename V = int32_t>
inline V extGcd(V a, V b, V& x, V& y) {
  DEBUG_TRUE(is_signed<V>::value);
  bool negativeA = false;
  if (a < 0) {
    negativeA = true;
    a = -a;
  }
  bool negativeB = false;
  if (b < 0) {
    negativeB = true;
    b = -b;
  }
  x = 1;
  y = 0;
  V xTmp = 0;
  V yTmp = 1;
  while (b) {
    V q = a / b;
    tie(x, xTmp) = make_tuple(xTmp, x - q * xTmp);
    tie(y, yTmp) = make_tuple(yTmp, y - q * yTmp);
    tie(a, b) = make_tuple(b, a - q * b);
  }
  if (negativeA) {
    x = -x;
  }
  if (negativeB) {
    y = -y;
  }
  return a;
}

} // namespace math
