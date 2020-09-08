#pragma once

#include <unordered_map>

#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

// Calculates minimum non-negative x where k*a^x=b (% mod), a and m are coprime
//
// Returns whether x exists
template<typename V = int32_t, typename V_SQR = int64_t>
inline bool logModCoPrime(V a, V b, V mod, V& res, V k = 1) {
  fixModInline(a, mod);
  fixModInline(b, mod);
  V n = static_cast<V>(sqrt(mod) + 1);
  unordered_map<V, V> vals;
  for (int q = 0, cur = b; q <= n; ++q) {
    vals[cur] = q;
    cur = mulMod<V, V_SQR>(cur, a, mod);
  }
  V an = expMod<V, V, V_SQR>(a, n, mod);
  for (int p = 1, cur = fixMod(k, mod); p <= n; ++p) {
    cur = mulMod<V, V_SQR>(cur, an, mod);
    auto it = vals.find(cur);
    if (it != vals.end()) {
      res = n * p - it->second;
      return true;
    }
  }
  return false;
}

} // namespace math
