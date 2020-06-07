#pragma once

#include <utility>

#include "math/mod/add.h"
#include "math/mod/mul.h"
#include "math/mod/slight_fix.h"
#include "math/mod/sub.h"

using namespace std;

namespace math {

// Computes {F(n), F(n+1)}, using
//   F(2k)=F(k)(2F(k+1)-F(k))
//   F(2k+1)=F(k+1)^2+F(k)^2
template<typename V = int, typename IDX = int, typename V_SQR = long long>
inline pair<V, V> fib(IDX n, const V& mod = 1000000007) {
  if (!n) {
    return {0, slightFixMod<V>(1, mod)};
  }
  V a, b;
  tie(a, b) = fib<V, IDX, V_SQR>(n >> 1, mod);
  V c = mulMod<V, V_SQR>(a, subMod<V>(addMod<V>(b, b, mod), a, mod), mod);
  V d =
      addMod<V>(mulMod<V, V_SQR>(a, a, mod), mulMod<V, V_SQR>(b, b, mod), mod);
  if (n & 1) {
    return {d, addMod<V>(c, d, mod)};
  } else {
    return {c, d};
  }
}

} // namespace math
