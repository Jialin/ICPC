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
      // => COMPLEX_INIT
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
      // => COMPLEX_CONJ
      // => COMPLEX_SUB
      _as[j] = (_as[i] * _as[i] - (_as[j] * _as[j]).conj()) * DOWN_QUART;
      // => COMPLEX_INIT_CONJ
      _as[i].initConj(_as[j]);
    }
    fft.fft(_as, false, pow2);
    for (auto& c : _as) {
      // => COMPLEX_DIV_INLINE_DOUBLE
      c /= pow2;
    }
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
