#pragma once

#include "math/fft/fft_utils_macros.h"

#include "debug/debug.h"
#include "math/bit/next_pow2_32.h"
#include "math/complex/complex.h"
#include "math/constants/pi.h"

#ifdef FFT_UTILS_MUL_BIGINT
#include "math/bigint/bigint.h"
#endif

using namespace std;

namespace math {

template<typename T = double>
struct FFTUtils {
  inline FFTUtils(int capacity = -1) {
    if (capacity > 0) {
      capacity = nextPow2_32(capacity);
    }
    capacity = max(capacity, 2);
    _revs.reserve(capacity);
    _revs.resize(2);
    _revs[0] = 0;
    _revs[1] = 1;
    _roots.reserve(capacity | 1);
    _roots.resize(3);
    _roots[0].init(0, 0);
    _roots[1].init(1, 0);
    _roots[2].init(1, 0);
    _initCapacity(capacity);
    _cs.reserve(capacity);
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
    _cs2.reserve(capacity);
    _cs3.reserve(capacity);
#endif
  }

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
    fft(_cs, false, pow2);
    _c.init(0, -0.25);
    for (int i = 0; i <= (pow2 >> 1); ++i) {
      int j = (pow2 - i) & (pow2 - 1);
      _c2.initMul(_cs[i] * _cs[i] - (_cs[j] * _cs[j]).conj(), _c);
      _cs[i].initConj(_c2);
      _cs[j] = _c2;
    }
    fft(_cs, false, pow2);
    for (auto& c : _cs) {
      c /= pow2;
    }
    _shrink(_cs);
    return _cs;
  }
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
  inline void
  mul(vector<Complex<T>>& x, vector<Complex<T>>& y, vector<Complex<T>>& res) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    fft(x, false, pow2);
    fft(y, false, pow2);
    res.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      res[i].initMul(x[i], y[i]);
    }
    fft(res, true, pow2);
    _shrink(res);
  }
#endif

  inline void fft(vector<Complex<T>>& cs, bool invert, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? cs.size() : n);
    _initCapacity(pow2);
    _expand(pow2, cs);
    int shift = __builtin_ctz(_revs.size()) - __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = _revs[i] >> shift;
      if (i < j) {
        swap(cs[i], cs[j]);
      }
    }
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0, l2 = l << 1; i < pow2; i += l2) {
        int step = invert ? -1 : 1;
        for (int j = 0, k = invert ? (l << 1) : l; j < l; ++j, k += step) {
          _c.initMul(cs[i + j + l], _roots[k]);
          if (invert && j) {
            _c.flip();
          }
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

  inline void _expand(int pow2, vector<Complex<T>>& cs) {
    for (size_t i = cs.size(); i < pow2; ++i) {
      cs.emplace_back(0, 0);
    }
  }

#ifdef _FFT_UTILS_SHRINK
  inline void _shrink(vector<Complex<T>>& cs) {
    for (; cs.size() > 1 && cs.back().real < 0.5; cs.pop_back()) {}
  }
#endif

  inline void _initCapacity(int pow2) {
    if (_revs.size() >= pow2) {
      return;
    }
    int oldPow2 = _revs.size(), lgN = __builtin_ctz(pow2);
    _revs.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      _revs[i] = (_revs[i >> 1] >> 1) + ((i & 1) << (lgN - 1));
    }
    _roots.resize(pow2 | 1);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      T angle = PI / i, baseAngle = angle * 2;
      for (int j = i; j < i << 1; j += 2, angle += baseAngle) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1].initPolar(1, angle);
      }
    }
    _roots[pow2] = _roots[pow2 >> 1];
  }

  vector<int> _revs;
  vector<Complex<T>> _roots, _cs;
  Complex<T> _c;
#ifdef _FFT_UTILS_COMPLEX_2
  Complex<T> _c2;
#endif
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
  vector<Complex<T>> _cs2, _cs3;
#endif
};

} // namespace math
