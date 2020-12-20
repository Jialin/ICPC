#pragma once

// clang-format off
#include "math/fft/fft_utils_macros.h"
#include "math/complex/complex_macros.h"
// clang-format on

#include <unordered_map>

#include "math/complex/complex.h"
#include "math/fft/fft_utils_macros.h"

#ifdef FFT_UTILS_MUL_BIGINT
#include "math/bigint/bigint.h"
#endif

#if defined(FFT_UTILS_MUL_COMPLEX_VECTOR) ||                                   \
    defined(_FFT_UTILS_COMPLEX_VECTOR_3)
#include "math/bit/next_pow2_32.h"
#endif

using namespace std;

namespace math {

template<typename T = double>
struct FFTUtils {
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
  inline FFTUtils(int capacity = -1) {
    _ws.reserve(32);
    _revs.reserve(32);
    if (capacity > 0) {
      capacity = nextPow2_32(capacity);
      _cs1.reserve(capacity);
      _cs2.reserve(capacity);
      _cs3.reserve(capacity);
    }
  }
#elif
  inline FFTUtils() {
    _ws.reserve(32);
    _revs.reserve(32);
  }
#endif

#ifdef FFT_UTILS_MUL_BIGINT
  template<int GROUP, typename BASE_SQR>
  inline void
  mul(const BigInt<GROUP, BASE_SQR>& x,
      const BigInt<GROUP, BASE_SQR>& y,
      BigInt<GROUP, BASE_SQR>& res) {
    x.outputComplexVector(_cs1);
    y.outputComplexVector(_cs2);
    mul(_cs1, _cs2, _cs3);
    res = _cs3;
  }
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
  inline void
  mul(vector<Complex<T>>& x, vector<Complex<T>>& y, vector<Complex<T>>& res) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    _expand(pow2, x);
    _expand(pow2, y);
    fft(pow2, x, false);
    fft(pow2, y, false);
    res.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      res[i].initMul(x[i], y[i]);
    }
    fft(pow2, res, true);
    _shrink(res);
  }
#endif

  inline void fft(int pow2, vector<Complex<T>>& cs, bool invert) {
    _initSize(pow2);
    const auto& rev = _revs[pow2];
    for (int i = 0; i < pow2; ++i) {
      if (i < rev[i]) {
        swap(cs[i], cs[rev[i]]);
      }
    }
    const auto& w = _ws[pow2];
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0, l2 = l << 1, step = pow2 / l2; i < pow2; i += l2) {
        for (int j = 0, wIdx = invert ? pow2 : 0; j < l;
             ++j, wIdx += invert ? -step : step) {
          _c.initMul(cs[i + j + l], w[wIdx]);
          cs[i + j + l].initSub(cs[i + j], _c);
          cs[i + j] += _c;
        }
      }
    }
    if (invert) {
      for (int i = 0; i < pow2; ++i) {
        cs[i] /= pow2;
      }
    }
  }

  inline void _initSize(int pow2) {
    if (_ws.count(pow2)) {
      return;
    }
    auto& w = _ws[pow2];
    w.resize(pow2 + 1);
    w[0].init(1, 0);
    auto& rev = _revs[pow2];
    rev.resize(pow2);
    T angle = acos(static_cast<T>(-1)) * 2 / pow2;
    _c.initPolar(1, angle);
    int logN = __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      w[i + 1].initMul(w[i], _c);
      rev[i] = 0;
      for (int j = i; j; j &= j - 1) {
        rev[i] |= 1 << (logN - 1 - __builtin_ctz(j));
      }
    }
  }

  inline void _expand(int n, vector<Complex<T>>& cs) {
    for (int i = cs.size(); i < n; ++i) {
      cs.emplace_back(0, 0);
    }
  }

  inline void _shrink(vector<Complex<T>>& cs) {
    for (; cs.size() > 1 && cs.back().real < 0.5; cs.pop_back()) {}
  }

  unordered_map<int, vector<Complex<T>>> _ws;
  unordered_map<int, vector<int>> _revs;
  Complex<T> _c;
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
  vector<Complex<T>> _cs1, _cs2, _cs3;
#endif
};

} // namespace math
