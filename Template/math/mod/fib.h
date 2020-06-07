#pragma once

#include <utility>

using namespace std;

namespace math {

// Computes {F(n), F(n+1)}, using
//   F(2k)=F(k)(2F(k+1)-F(k))
//   F(2k+1)=F(k+1)^2+F(k)^2
template<typename V = int, IDX = int, V_DOUBLE = int, V_SQR = long long>
inline pair<V, V> fib(IDX n, const V& mod) {
  if (!n) {
    return {0, fix(1, mod)};
  }
  tie(a, b) = fib(n >> 1);

  slightFixModInline<V>(v, mod);
  if (v < 0 || mod <= v) {
    assert(mod);
    v %= mod;
    slightFixModInline<V>(v, mod);
  }
}

} // namespace math
