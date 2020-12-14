#pragma once

#include "math/fib/fib.h"
#include "math/mod/add.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

namespace math {

// Computes generalized fibonacci F'(n) with given F'(0), F'(1),
//
// |F(k+2)| = |1 1| |F(k+1)|
// |F(k+1)|   |1 0| | F(k) |
//
// |1 1|n = |F(n+1)  F(n) |
// |1 0|    | F(n)  F(n-1)|
template<typename V = int, typename IDX = int, typename V_SQR = int64_t>
inline V fibGeneral(IDX n, V f0, V f1, const V& mod) {
  if (!n) {
    return fixMod<V>(f0, mod);
  }
  V a, b;
  tie(a, b) = fib<V, IDX, V_SQR>(n - 1, mod);
  return addMod<V>(
      mulMod<V, V_SQR>(a, f0, mod), mulMod<V, V_SQR>(b, f1, mod), mod);
}

} // namespace math
