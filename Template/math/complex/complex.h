#pragma once

#include "math/complex/complex_macros.h"

namespace math {

template<typename T = double>
struct Complex {
  inline Complex(T _real = 0, T _imag = 0) : real(_real), imag(_imag) {}

  // inline Complex<T> operator*(const Complex<T>& o) {
  //   return Complex(
  //       real_ * o.real_ - imag_ * o.imag_, real_ * o.imag_ + imag_ *
  //       o.real_);
  // }

  inline void operator+=(const Complex<T>& o) {
    real += o.real;
    imag += o.imag;
  }

  // inline void operator/=(const T& scale) {
  //   real_ /= scale;
  //   imag_ /= scale;
  // }

  inline void init(T _real = 0, T _imag = 0) {
    real = _real;
    imag = _imag;
  }

  inline void initPolar(T r, T theta) {
    real = r * cos(theta);
    imag = r * sin(theta);
  }

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

  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real = x.real - y.real;
    imag = x.imag - y.imag;
  }

  T real, imag;
};

} // namespace math
