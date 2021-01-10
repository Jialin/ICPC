#pragma once

#include "math/mod/mod_int_macros.h"

#if defined(MOD_INT_INV) || defined(MOD_INT_INV_INLINE)
#include "math/gcd/ext_gcd.h"
#endif

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

#ifdef MOD_INT_ASSIGN
  inline void operator=(const ModInt& o) {
    _v = o._v;
  }
#endif

#ifdef MOD_INT_NEGATE
  inline ModInt operator-() const {
    return ModInt(_v ? MOD - _v : 0);
  }
#endif

#ifdef MOD_INT_NEGATE_INLINE
  inline void negateInline() {
    if (_v) {
      _v = MOD - _v;
    }
  }
#endif

#ifdef MOD_INT_ADD
  inline ModInt operator+(const ModInt& o) const {
    return ModInt(_v + o._v);
  }
#endif

#ifdef MOD_INT_ADD_INLINE
  inline void operator+=(const ModInt& o) {
    _v += o._v;
    if (_v >= MOD) {
      _v -= MOD;
    }
  }
#endif

#ifdef MOD_INT_SUB_INLINE
  inline void operator-=(const ModInt& o) {
    _v -= o._v;
    if (_v < 0) {
      _v += MOD;
    }
  }
#endif

#ifdef MOD_INT_MUL
  inline ModInt operator*(const ModInt& o) const {
    return ModInt(fix(static_cast<V_SQR>(_v) * o._v));
  }
#endif

#ifdef MOD_INT_MUL_INLINE
  inline void operator*=(const ModInt& o) {
    _v = fix(static_cast<V_SQR>(_v) * o._v);
  }
#endif

#ifdef MOD_INT_DIV
  inline ModInt operator/(const ModInt& o) const {
    return *this * o.inv();
  }
#endif

#ifdef MOD_INT_DIV_INLINE
  inline void operator/=(const ModInt& o) {
    _v = fix(static_cast<V_SQR>(_v) * o.inv()._v);
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
    DEBUG_EQ(extGcd<V>(_v, MOD, x0, x1), 1);
#else
    extGcd<V>(_v, MOD, x0, x1);
#endif
    return ModInt(x0);
  }
#endif

#ifdef MOD_INT_INV_INLINE
  inline void invInline() {
    V x0, x1;
#ifdef LOCAL
    DEBUG_EQ(extGcd<V>(_v, MOD, x0, x1), 1);
#else
    extGcd<V>(_v, MOD, x0, x1);
#endif
    _v = fix(x0);
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

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const ModInt& v) {
    o << v._v;
    return o;
  }
#endif

  int _v;
};

} // namespace math

#ifdef LOCAL
template<typename V, typename V_SQR, V MOD>
inline string totype(const math::ModInt<V, V_SQR, MOD>& v) {
  return "ModInt<" + totype(V()) + "," + totype(V_SQR()) + "," + tostring(MOD) +
         ">";
}
#endif
