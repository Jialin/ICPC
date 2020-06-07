#pragma once

#include "math/fib/fib.h"
#include "math/mod/sub.h"

using namespace std;

namespace math {

// Computes sum{F(i) where i from 0 to n}
template<typename V = int, typename IDX = int, typename V_SQR = long long>
inline V fibPartialSum(IDX n, const V& mod = 1000000007) {
  if (n <= 0) {
    return 0;
  }
  return subMod<V>(fib<V, IDX, V_SQR>(n + 2, mod).first, 1, mod);
}

} // namespace math
