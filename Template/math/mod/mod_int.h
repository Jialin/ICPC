#pragma once

#include "math/mod/mod_int_macros.h"

#include "math/gcd/ext_gcd.h"

using namespace std;

namespace math {

template<typename V, typename V_SQR, V MOD>
struct ModInt {
  template<typename T>
  inline static V fix(T v) {
    if (v < 0) {
      v += MOD;
    } else if (v >= MOD) {
      v -= MOD;
    } else {
      return v;
    }
    if (v < 0 || v >= MOD) {
      v %= MOD;
    } else {
      return v;
    }
    if (v < 0) {
      v += MOD;
    } else if (v >= MOD) {
      v -= MOD;
    }
    return v;
  }

  inline ModInt(V v = 0) {
    _v = fix(v);
  }

#ifdef MOD_INT_ADD_INLINE
  inline void operator+=(const ModInt& o) {
    _v += o._v;
    if (_v >= MOD) {
      _v -= MOD;
    }
  }
#endif

#ifdef MOD_INT_MUL_INLINE
  inline void operator*=(const ModInt& o) {
    _v = fix(static_cast<V_SQR>(_v) * o._v);
  }
#endif

#ifdef MOD_INT_INIT_MUL
  inline void initMul(const ModInt& x, const ModInt& y) {
    _v = fix(static_cast<V_SQR>(x._v) * y._v);
  }
#endif

#ifdef MOD_INT_INIT_SUB
  inline void initSub(const ModInt& x, const ModInt& y) {
    _v = x._v - y._v;
    if (_v < 0) {
      _v += MOD;
    }
  }
#endif

#ifdef MOD_INT_INV
  inline ModInt inv() const {
    V x0, x1;
#ifdef LOCAL
    DEBUG_EQ(extGcd(_v, MOD, x0, x1), 1);
#else
    extGcd(_v, MOD, x0, x1);
#endif
    return ModInt(x0);
  }
#endif

#ifdef MOD_INT_EXP
  template<typename E>
  inline ModInt exp(E e) const {
    if (e < 0) {
      return inv().exp(-e);
    }
    ModInt res = 1, mul = *this;
    while (e) {
      if (e & 1) {
        res *= mul;
      }
      e >>= 1;
      if (e) {
        mul *= mul;
      }
    }
    return res;
  }
#endif

#ifdef MOD_INT_FLIP
  inline void flip() {
    if (MOD > 1) {
      _v = MOD - _v;
    }
  }
#endif

  int _v;
};

} // namespace math
