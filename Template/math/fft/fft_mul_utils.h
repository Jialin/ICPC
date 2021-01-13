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

// ^ FFT_MUL_UTILS_MUL_INT
#ifdef FFT_MUL_UTILS_MUL_INT
  const Complex<T> DOWN_QUART = Complex<T>(0, -0.25);

  template<typename V>
  inline const vector<Complex<T>>&
  mulInt(const vector<V>& xs, const vector<V>& ys, bool cyclic) {
    if (xs.empty() || ys.empty()) {
      _as.resize(1);
      // FFT_MUL_UTILS_MUL_INT => COMPLEX_INIT
      _as[0].init(0, 0);
      return _as;
    }
    int pow2 = nextPow2_32(
        cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1);
    _as.resize(pow2);
    for (size_t i = 0; i < pow2; ++i) {
      _as[i].init(i < xs.size() ? xs[i] : 0, i < ys.size() ? ys[i] : 0);
    }
    auto& fft = FFTUtils<T>::instance();
    fft.fft(_as, false, pow2);
    for (int i = 0; i <= (pow2 >> 1); ++i) {
      int j = (pow2 - i) & (pow2 - 1);
      // FFT_MUL_UTILS_MUL_INT => COMPLEX_MUL_INLINE
      _as[i] *= _as[i];
      if (i != j) {
        _as[j] *= _as[j];
        _as[j].imag = -_as[j].imag;
        _as[j].initSub(_as[i], _as[j]);
        // FFT_MUL_UTILS_MUL_INT => COMPLEX_DIV_INLINE_DOUBLE
        _as[j] /= pow2 << 2;
        swap(_as[j].real, _as[j].imag);
        _as[j].imag = -_as[j].imag;
      } else {
        _as[j].real = _as[j].imag / (pow2 << 1);
        _as[j].imag = 0;
      }
      // FFT_MUL_UTILS_MUL_INT => COMPLEX_INIT_CONJ
      _as[i].initConj(_as[j]);
    }
    fft.fft(_as, false, pow2);
    // FFT_MUL_UTILS_MUL_INT => _FFT_UTILS_SHRINK_COMPLEX_VECTOR
    _shrink(_as);
    return _as;
  }

  vector<Complex<T>> _as;
#endif

// ^ FFT_MUL_UTILS_MUL_INLINE_INT
#ifdef FFT_MUL_UTILS_MUL_INLINE_INT
  template<typename V>
  inline void mulInlineInt(vector<V>& xs, const vector<V>& ys, bool cyclic) {
    // FFT_MUL_UTILS_MUL_INLINE_INT => FFT_MUL_UTILS_MUL_INT
    const auto& cs = mulInt(xs, ys, cyclic);
    xs.resize(cs.size());
    for (size_t i = 0; i < cs.size(); ++i) {
      xs[i] = cs[i].real + 0.5;
    }
  }
#endif

#ifdef _FFT_UTILS_SHRINK_COMPLEX_VECTOR
  inline void _shrink(vector<Complex<T>>& cs) {
    for (; cs.size() > 1 && cs.back().real < 0.5; cs.pop_back()) {}
  }
#endif
};

} // namespace math
