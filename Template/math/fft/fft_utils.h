#pragma once

#include <complex>
#include <unordered_map>

#ifdef FFT_UTILS_ALL
#define FFT_UTILS_MUL_BIGINT
#define FFT_UTILS_MUL_COMPLEX_VECTOR
#endif

#ifdef FFT_UTILS_MUL_BIGINT
#define BIGINT_ASSIGN_COMPLEX_VECTOR
#define BIGINT_OUTPUT_COMPLEX_VECTOR
#define FFT_UTILS_MUL_COMPLEX_VECTOR
#endif

#ifdef FFT_UTILS_MUL_BIGINT
#include "math/bigint.h"
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
#include "math/bit/next_pow2_32.h"
#endif

using namespace std;

namespace math {

template<typename T = double>
struct FFTUtils {
  inline FFTUtils()
      : _ws(unordered_map<int, vector<complex<T>>>(32)),
        _revs(unordered_map<int, vector<int>>(32)) {}

#ifdef FFT_UTILS_MUL_BIGINT
  template<int GROUP, typename BASE_SQR>
  inline void
  mul(const BigInt<GROUP, BASE_SQR>& x,
      const BigInt<GROUP, BASE_SQR>& y,
      BigInt<GROUP, BASE_SQR>& res) {
    vector<complex<T>> xs, ys, zs;
    x.outputComplexVector(xs);
    DEBUGV(xs);
    y.outputComplexVector(ys);
    DEBUGV(ys);
    mul(xs, ys, zs);
    DEBUGV(zs);
    res = zs;
  }
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
  inline void
  mul(vector<complex<T>>& x, vector<complex<T>>& y, vector<complex<T>>& res) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    _expand(pow2, x);
    _expand(pow2, y);
    fft(pow2, x, false);
    fft(pow2, y, false);
    res.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      res[i] = x[i] * y[i];
    }
    fft(pow2, res, true);
    _shrink(res);
  }
#endif

  inline void fft(int pow2, vector<complex<T>>& cs, bool invert) {
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
          _tmpC = cs[i + j + l] * w[wIdx];
          cs[i + j + l] = cs[i + j] - _tmpC;
          cs[i + j] += _tmpC;
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
    w.reserve(pow2 + 1);
    w.emplace_back(1, 0);
    auto& rev = _revs[pow2];
    rev.reserve(pow2);
    T angle = acos(static_cast<T>(-1)) * 2 / pow2;
    _tmpC = complex<T>(cos(angle), sin(angle));
    int logN = __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      w.push_back(w.back() * _tmpC);
      rev[i] = 0;
      for (int j = i; j; j &= j - 1) {
        rev[i] |= 1 << (logN - 1 - __builtin_ctz(j));
      }
    }
  }

  inline void _expand(int n, vector<complex<T>>& cs) {
    for (int i = cs.size(); i < n; ++i) {
      cs.emplace_back(0, 0);
    }
  }

  inline void _shrink(vector<complex<T>>& cs) {
    for (; cs.size() > 1 && cs.back().real() < 0.5; cs.pop_back()) {}
  }

  unordered_map<int, vector<complex<T>>> _ws;
  unordered_map<int, vector<int>> _revs;
  complex<T> _tmpC;
};

} // namespace math
