#pragma once

#include "debug/debug_basic.h"
#include "math/complex/complex_macros.h"

namespace math {

template<typename T = double>
struct Complex {
  inline Complex(T _real = 0, T _imag = 0) : real(_real), imag(_imag) {}

#ifdef COMPLEX_ADD_INLINE
  inline void operator+=(const Complex<T>& o) {
    real += o.real;
    imag += o.imag;
  }
#endif

#ifdef COMPLEX_DIV_INLINE_DOUBLE
  inline void operator/=(T scale) {
    real /= scale;
    imag /= scale;
  }
#endif

#ifdef COMPLEX_INIT
  inline void init(T _real = 0, T _imag = 0) {
    real = _real;
    imag = _imag;
  }
#endif

#ifdef COMPLEX_INIT_POLAR
  inline void initPolar(T r, T theta) {
    real = r * cos(theta);
    imag = r * sin(theta);
  }
#endif

#ifdef COMPLEX_INIT_MUL
  inline void initMul(const Complex<T>& x, const Complex<T>& y) {
    DEBUGF_NE(
        this,
        &x,
        "in a.initMul(b,c), a and b should not reference to the same instance");
    DEBUGF_NE(
        this,
        &y,
        "in a.initMul(b,c), a and c should not reference to the same instance");
    real = x.real * y.real - x.imag * y.imag;
    imag = x.real * y.imag + x.imag * y.real;
  }
#endif

#ifdef COMPLEX_INIT_SUB
  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real = x.real - y.real;
    imag = x.imag - y.imag;
  }
#endif

  T real, imag;
};

} // namespace math
