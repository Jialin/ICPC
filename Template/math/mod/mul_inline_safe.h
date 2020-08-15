#pragma once

using namespace std;

#include "math/mod/add.h"
#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
inline void mulModInlineSafe(V& res, V x, const V& mod) {
  fixModInline<V>(res, mod);
  fixModInline<V>(x, mod);
  if (!res || !x) {
    res = 0;
  } else if (res < mod / x) {
    res *= x;
  } else if (res <= numeric_limits<V_SQR>::max() / x) {
    res = static_cast<V_SQR>(res) * x % mod;
  } else {
    V newRes = 0;
    for (; x > 0; x >>= 1) {
      if (x & 1) {
        newRes = addMod<V>(newRes, res, mod);
      }
      res = addMod<V>(res, res, mod);
    }
    res = newRes;
  }
}

} // namespace math
