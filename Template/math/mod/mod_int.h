// !macro_gen
// ALL MOD_INT_ALL
#pragma once

#include "debug/debug_declare.h"
#include "math/mod/mod_int_macros.h"

#ifdef _MOD_INT_EXTGCD
#include "math/gcd/ext_gcd.h"
#endif

using namespace std;

namespace math {

template<typename _V, typename _V_SQR, _V _MOD>
struct ModInt {
#ifdef MOD_INT_TYPEDEF_V // ^
  typedef _V V;
#endif
#ifdef MOD_INT_TYPEDEF_V_SQR // ^
  typedef _V_SQR V_SQR;
#endif
#ifdef MOD_INT_CONST_MOD // ^
  static const _V MOD = _MOD;
#endif

  template<typename T>
  inline static _V fix(T v) {
    if (v < 0) {
      v += _MOD;
    } else if (v >= _MOD) {
      v -= _MOD;
    } else {
      return v;
    }
    if (v < 0 || v >= _MOD) {
      v %= _MOD;
    } else {
      return v;
    }
    if (v < 0) {
      v += _MOD;
    } else if (v >= _MOD) {
      v -= _MOD;
    }
    return v;
  }

  inline ModInt(_V_SQR v = 0) {
    _v = fix(v);
  }

#ifdef MOD_INT_EQ // ^
inline bool operator==(const ModInt& o) const {
  return _v == o._v;
}
#endif

#ifdef MOD_INT_ASSIGN // ^
  inline void operator=(const ModInt& o) {
    _v = o._v;
  }
#endif

#ifdef MOD_INT_NEGATE // ^
  inline ModInt operator-() const {
    return ModInt(_v ? _MOD - _v : 0);
  }
#endif

#ifdef MOD_INT_NEGATE_INLINE // ^
  inline void negateInline() {
    if (_v) {
      _v = _MOD - _v;
    }
  }
#endif

#ifdef MOD_INT_ADD // ^
  inline ModInt operator+(const ModInt& o) const {
    return ModInt(_v + o._v);
  }
#endif

#ifdef MOD_INT_ADD_INLINE // ^
  inline void operator+=(const ModInt& o) {
    _v += o._v;
    if (_v >= _MOD) {
      _v -= _MOD;
    }
  }
#endif

#ifdef MOD_INT_SUB // ^
  inline ModInt operator-(const ModInt& o) const {
    return ModInt(_v - o._v);
  }
#endif

#ifdef MOD_INT_SUB_INLINE // ^
  inline void operator-=(const ModInt& o) {
    _v -= o._v;
    if (_v < 0) {
      _v += _MOD;
    }
  }
#endif

#ifdef MOD_INT_MUL // ^
  inline ModInt operator*(const ModInt& o) const {
    return ModInt(fix(static_cast<_V_SQR>(_v) * o._v));
  }
#endif

#ifdef MOD_INT_MUL_INLINE // ^
  inline void operator*=(const ModInt& o) {
    _v = fix(static_cast<_V_SQR>(_v) * o._v);
  }
#endif

#ifdef MOD_INT_DIV // ^
  inline ModInt operator/(const ModInt& o) const {
    // MOD_INT_DIV => MOD_INT_INV
    return *this * o.inv();
  }
#endif

#ifdef MOD_INT_DIV_INLINE // ^
  inline void operator/=(const ModInt& o) {
    // MOD_INT_DIV_INLINE => MOD_INT_INV
    _v = fix(static_cast<_V_SQR>(_v) * o.inv()._v);
  }
#endif

#ifdef MOD_INT_INIT_MUL // ^
  inline void initMul(const ModInt& x, const ModInt& y) {
    _v = fix(static_cast<_V_SQR>(x._v) * y._v);
  }
#endif

#ifdef MOD_INT_INIT_ADD // ^
  inline void initAdd(const ModInt& x, const ModInt& y) {
    _v = x._v + y._v;
    if (_v > _MOD) {
      _v -= _MOD;
    }
  }
#endif

#ifdef MOD_INT_INIT_SUB // ^
  inline void initSub(const ModInt& x, const ModInt& y) {
    _v = x._v - y._v;
    if (_v < 0) {
      _v += _MOD;
    }
  }
#endif

#ifdef MOD_INT_INV // ^
  inline ModInt inv() const {
    ModInt res = *this;
    // MOD_INT_INV => MOD_INT_INV_INLINE
    res.invInline();
    return res;
  }
#endif

#ifdef MOD_INT_INV_INLINE // ^
  inline void invInline() {
    _V x0, x1;
    // MOD_INT_INV_INLINE => _MOD_INT_EXTGCD
#ifdef LOCAL
    DEBUG_EQ(extGcd<_V>(_v, _MOD, x0, x1), 1);
#else
    extGcd<_V>(_v, _MOD, x0, x1);
#endif
    _v = fix(x0);
  }
#endif

#ifdef MOD_INT_EXP // ^
  template<typename E>
  inline ModInt exp(E e) const {
    if (e < 0) {
      // MOD_INT_EXP => MOD_INT_INV
      return inv().exp(-e);
    }
    _V_SQR res = 1, mul = _v;
    while (e) {
      if (e & 1) {
        res = res * mul % _MOD;
      }
      e >>= 1;
      if (e) {
        mul = mul * mul % _MOD;
      }
    }
    return res;
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
  return "ModInt<" + totype(V()) + "," + totype(V_SQR()) + "," + tostring(MOD) + ">";
}
#endif
