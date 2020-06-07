#pragma once

#include "math/matrix/matrix.h"
#include "math/mod/add.h"
#include "math/mod/mul.h"

namespace math {

template<typename V = int, typename V_SQR = long long>
inline void matrixMulModInline(
    Matrix<V>& res, const Matrix<V>& a, const Matrix<V>& b, const V& mod) {
  assert(a.m() == b.n());
  res.init(a.n(), b.m());
  for (int i = a.n() - 1; i >= 0; --i) {
    for (int j = b.m() - 1; j >= 0; --j) {
      V& subRes = res.at(i, j);
      subRes = 0;
      for (int k = a.m() - 1; k >= 0; --k) {
        subRes = addMod<V>(
            subRes, mulMod<V, V_SQR>(a.at(i, k), b.at(k, j), mod), mod);
      }
    }
  }
}

} // namespace math
