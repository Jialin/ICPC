#pragma once

#include "debug/debug.h"
#include "math/mod/add.h"
#include "math/mod/mul_safe.h"

namespace math {

template<typename MATRIX, typename V = int, typename V_SQR = int64_t>
inline void matrixMulModInline(
    MATRIX& res, const MATRIX& a, const MATRIX& b, const V& mod) {
  DEBUG_EQ(a._m, b._n);
  res.init(a._n, b._m);
  for (int i = a._n - 1; i >= 0; --i) {
    for (int j = b._m - 1; j >= 0; --j) {
      V& subRes = res._vs[i][j];
      subRes = 0;
      for (int k = a._m - 1; k >= 0; --k) {
        subRes = addMod<V>(
            subRes, mulModSafe<V, V_SQR>(a._vs[i][k], b._vs[k][j], mod), mod);
      }
    }
  }
}

} // namespace math
