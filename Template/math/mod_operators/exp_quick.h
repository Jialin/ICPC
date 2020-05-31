#pragma once

#include <vector>

#include "math/mod_operators/mul_inline.h"

using namespace std;

namespace math {

template <typename V = int32_t, typename EXP = int32_t, typename VV = int64_t>
inline V expModQuick(vector<V> &powList, V base, EXP exp, const V &mod) {
  assert(exp >= 0);
  fixModInline<V>(base, mod);
  if (powList.empty()) {
    powList.emplace_back(base);
  }
  V res = 1;
  fixModInline<V>(res, mod);
  for (size_t i = 0; exp > 0; exp >>= 1, ++i) {
    if (exp & 1) {
      while (i >= powList.size()) {
        powList.emplace_back(powList.back());
        mulModInline<V, VV>(powList.back(), powList.back(), mod);
      }
      mulModInline<V, VV>(res, powList[i], mod);
    }
  }
  return res;
}

} // namespace math
