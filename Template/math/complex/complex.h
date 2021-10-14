// !macro_gen
// ALL COMPLEX_ALL
#pragma once

#include <cmath>

#include "debug/debug_basic.h"
#include "math/complex/complex_macros.h"

namespace math {

template<typename T = double>
struct Complex {
  inline Complex(T _real = 0, T _imag = 0) : real(_real), imag(_imag) {}

#ifdef COMPLEX_ASSIGN // ^
  inline void operator=(const Complex<T>& o) {
    real = o.real;
    imag = o.imag;
  }
#endif

#ifdef COMPLEX_ADD // ^
  inline Complex<T> operator+(const Complex<T>& o) const {
    return Complex<T>(real + o.real, imag + o.imag);
  }
#endif

#ifdef COMPLEX_ADD_INLINE // ^
  inline void operator+=(const Complex<T>& o) {
    real += o.real;
    imag += o.imag;
  }
#endif

#ifdef COMPLEX_SUB // ^
  inline Complex<T> operator-(const Complex<T>& o) const {
    return Complex<T>(real - o.real, imag - o.imag);
  }
#endif

#ifdef COMPLEX_MUL // ^
  inline Complex<T> operator*(const Complex<T>& o) const {
    return Complex<T>(real * o.real - imag * o.imag, real * o.imag + o.real * imag);
  }
#endif

#ifdef COMPLEX_MUL_INLINE // ^
  inline void operator*=(const Complex<T>& o) {
    T realCopy = real, oRealCopy = o.real;
    real = realCopy * oRealCopy - imag * o.imag;
    imag = realCopy * o.imag + imag * oRealCopy;
  }
#endif

#ifdef COMPLEX_DIV_INLINE_DOUBLE // ^
  inline void operator/=(T scale) {
    real /= scale;
    imag /= scale;
  }
#endif

#ifdef COMPLEX_INIT // ^
  inline void init(T _real = 0, T _imag = 0) {
    real = _real;
    imag = _imag;
  }
#endif

#ifdef COMPLEX_INIT_CONJ // ^
  inline void initConj(const Complex<T>& o) {
    real = o.real;
    imag = -o.imag;
  }
#endif

#ifdef COMPLEX_INIT_POLAR // ^
  inline void initPolar(T r, T theta) {
    real = r * cos(theta);
    imag = r * sin(theta);
  }
#endif

#ifdef COMPLEX_INIT_MUL // ^
  inline void initMul(const Complex<T>& x, const Complex<T>& y) {
    T originalReal = x.real;
    real = originalReal * y.real - x.imag * y.imag;
    imag = originalReal * y.imag + x.imag * y.real;
  }
#endif

#ifdef COMPLEX_INIT_SUB // ^
  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real = x.real - y.real;
    imag = x.imag - y.imag;
  }
#endif

#ifdef COMPLEX_CONJ // ^
  inline Complex<T> conj() const {
    return Complex<T>(real, -imag);
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const Complex<T>& v) {
    o << tostring(v.real) << (v.imag >= 0 ? "+" : "") << tostring(v.imag) + "i";
    return o;
  }
#endif

  T real, imag;
};

} // namespace math

#ifdef LOCAL
template<typename T>
inline string totype(const math::Complex<T>& v) {
  return "Complex<" + totype(v.real) + ">";
}
#endif
