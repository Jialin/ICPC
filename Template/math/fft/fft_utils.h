#pragma once

#include <unordered_map>

#include "math/fft/fft_utils_macros.h"

#include "math/complex/complex.h"
#include "math/constants/pi.h"

#ifdef FFT_UTILS_MUL_BIGINT
#include "math/bigint/bigint.h"
#endif

#if defined(FFT_UTILS_MUL_COMPLEX_VECTOR) || defined(FFT_UTILS_MUL_INT) ||     \
    defined(_FFT_UTILS_COMPLEX_VECTOR_3)
#include "math/bit/next_pow2_32.h"
#endif

using namespace std;

namespace math {

template<typename T = double>
struct FFTUtils {
#if defined(_FFT_UTILS_COMPLEX_VECTOR_1) || defined(_FFT_UTILS_COMPLEX_VECTOR_3)
  inline FFTUtils(int capacity = -1) {
    if (capacity > 0) {
      capacity = nextPow2_32(capacity);
      _cs.reserve(capacity);
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
      _cs2.reserve(capacity);
      _cs3.reserve(capacity);
#endif
    }
  }
#endif

#ifdef FFT_UTILS_MUL_BIGINT
  template<int GROUP, typename BASE_SQR>
  inline void
  mul(const BigInt<GROUP, BASE_SQR>& x,
      const BigInt<GROUP, BASE_SQR>& y,
      BigInt<GROUP, BASE_SQR>& res) {
    res = mul(x._vs, y._vs);
  }
#endif

#ifdef FFT_UTILS_MUL_INT
  inline const vector<Complex<T>>&
  mul(const vector<int>& x, const vector<int>& y) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    _cs.resize(pow2);
    for (size_t i = 0; i < pow2; ++i) {
      _cs[i].init(i < x.size() ? x[i] : 0, i < y.size() ? y[i] : 0);
    }
    fft(pow2, _cs, false);
    _c.init(0, -0.25);
    for (int i = 0; i <= (pow2 >> 1); ++i) {
      int j = (pow2 - i) & (pow2 - 1);
      _c2.initMul(_cs[i] * _cs[i] - (_cs[j] * _cs[j]).conj(), _c);
      _cs[i].initConj(_c2);
      _cs[j] = _c2;
    }
    fft(pow2, _cs, false);
    _shrink(_cs);
    for (auto& c : _cs) {
      c /= pow2;
    }
    return _cs;
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

  inline void _expand(int n, vector<Complex<T>>& cs) {
    for (int i = cs.size(); i < n; ++i) {
      cs.emplace_back(0, 0);
    }
  }
#endif

  inline void fft(int pow2, vector<Complex<T>>& cs, bool invert) {
    DEBUG_EQ(__builtin_popcount(pow2), 1);
    for (int i = 1, j = 0; i < pow2; ++i) {
      int bit = pow2 >> 1;
      for (; j & bit; bit >>= 1) {
        j ^= bit;
      }
      j ^= bit;
      if (i < j) {
        swap(cs[i], cs[j]);
      }
    }
    for (int l = 1; l < pow2; l <<= 1) {
      _c.initPolar(1, invert ? -PI / l : PI / l);
      for (int i = 0, l2 = l << 1; i < pow2; i += l2) {
        _c2.init(1, 0);
        for (int j = 0; j < l; ++j) {
          _c3.initMul(cs[i + j + l], _c2);
          cs[i + j + l].initSub(cs[i + j], _c3);
          cs[i + j] += _c3;
          _c2 *= _c;
        }
      }
    }
    if (invert) {
      for (int i = 0; i < pow2; ++i) {
        cs[i] /= pow2;
      }
    }
  }

  inline void _shrink(vector<Complex<T>>& cs) {
    for (; cs.size() > 1 && cs.back().real < 0.5; cs.pop_back()) {}
  }

  Complex<T> _c, _c2, _c3;
#ifdef _FFT_UTILS_COMPLEX_VECTOR_1
  vector<Complex<T>> _cs;
#endif
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
  vector<Complex<T>> _cs2, _cs3;
#endif
};

} // namespace math
