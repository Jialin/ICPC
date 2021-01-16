// ALL FFT_MUL_UTILS_ALL
#pragma once

#include "math/complex/complex_macros.h" // INCLUDE
#include "math/fft/fft_utils_macros.h"   // INCLUDE

#include "math/bit/next_pow2_32.h"
#include "math/complex/complex.h"
#include "math/fft/fft_utils.h"

using namespace std;

namespace math {

template<typename T = double>
struct FFTMulUtils {
  inline static FFTMulUtils& instance() {
    static FFTMulUtils instance;
    return instance;
  }

// ^ FFT_MUL_UTILS_MUL_REAL
#ifdef FFT_MUL_UTILS_MUL_REAL
  template<typename R>
  inline const vector<Complex<T>>&
  mulReal(const vector<R>& xs, const vector<R>& ys, bool cyclic) {
    static vector<Complex<T>> cs;
    if (xs.empty() || ys.empty()) {
      cs.resize(1);
      // FFT_MUL_UTILS_MUL_REAL => COMPLEX_INIT
      cs[0].init(0, 0);
      return cs;
    }
    int pow2 = nextPow2_32(
        cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1);
    cs.resize(pow2);
    for (size_t i = 0; i < pow2; ++i) {
      cs[i].init(i < xs.size() ? xs[i] : 0, i < ys.size() ? ys[i] : 0);
    }
    auto& fft = FFTUtils<T>::instance();
    fft.fft(cs, false, pow2);
    for (int i = 0; i <= (pow2 >> 1); ++i) {
      int j = (pow2 - i) & (pow2 - 1);
      // FFT_MUL_UTILS_MUL_REAL => COMPLEX_MUL_INLINE
      cs[i] *= cs[i];
      if (i != j) {
        cs[j] *= cs[j];
        cs[j].imag = -cs[j].imag;
        cs[j].initSub(cs[i], cs[j]);
        // FFT_MUL_UTILS_MUL_REAL => COMPLEX_DIV_INLINE_DOUBLE
        cs[j] /= pow2 << 2;
        swap(cs[j].real, cs[j].imag);
        cs[j].imag = -cs[j].imag;
      } else {
        cs[j].real = cs[j].imag / (pow2 << 1);
        cs[j].imag = 0;
      }
      // FFT_MUL_UTILS_MUL_REAL => COMPLEX_INIT_CONJ
      cs[i].initConj(cs[j]);
    }
    fft.fft(cs, false, pow2);
    if (is_integral<R>::value) {
      // FFT_MUL_UTILS_MUL_REAL => _FFT_UTILS_SHRINK_COMPLEX_VECTOR
      _shrink(cs);
    }
    return cs;
  }
#endif

// ^ FFT_MUL_UTILS_MUL_INLINE_REAL
#ifdef FFT_MUL_UTILS_MUL_INLINE_REAL
  template<typename R>
  inline void mulInlineReal(vector<R>& xs, const vector<R>& ys, bool cyclic) {
    // FFT_MUL_UTILS_MUL_INLINE_REAL => FFT_MUL_UTILS_MUL_REAL
    const auto& cs = mulReal(xs, ys, cyclic);
    xs.resize(cs.size());
    for (size_t i = 0; i < cs.size(); ++i) {
      xs[i] = is_integral<R>::value ? cs[i].real + 0.5 : cs[i].real;
    }
  }
#endif

#ifdef _FFT_UTILS_SHRINK_COMPLEX_VECTOR
  inline void _shrink(vector<Complex<T>>& cs) {
    for (; cs.size() > 1; cs.pop_back()) {
      T real = cs.back().real;
      if (real < -0.5 || real > 0.5) {
        break;
      }
    }
  }
#endif
};

} // namespace math
