#pragma once

#include "math/gcd/ext_gcd.h"
#include "math/mod/add.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

namespace math {

// Reduces
//   x = a1 (mod n1) and
//   x = a2 (mod n2)
// to
//   x = r (mod lcm(n1, n2))
template<typename V = int32_t, typename V_SQR = int64_t>
inline void chineseRemainder(V a1, V n1, V a2, V n2, V& r, V& lcm) {
  a1 = fixMod<V>(a1, n1);
  a2 = fixMod<V>(a2, n2);
  V x1, x2, gcd = extGcd<V>(n1, n2, x1, x2);
  lcm = n1 / gcd * n2;
  x1 = mulMod<V, V_SQR>(fixMod<V>(x1, lcm), n1 / gcd, lcm);
  x2 = mulMod<V, V_SQR>(fixMod<V>(x2, lcm), n2 / gcd, lcm);
  lcm = n1 / gcd * n2;
  r = addMod<V>(
      mulMod<V, V_SQR>(a1, x2, lcm), mulMod<V, V_SQR>(a2, x1, lcm), lcm);
}

} // namespace math
