#pragma once

#include "math/fft/fft_utils_macros.h"

#include "math/bit/next_pow2_32.h"
#include "math/complex/complex.h"
#include "math/constants/pi.h"

#ifdef FFT_UTILS_ONLINE_MOD
#include "math/mod/mod_int.h"
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
    _roots.reserve(capacity);
    _roots.resize(2);
    _roots[0].init(0, 0);
    _roots[1].init(1, 0);
    _initCapacity(capacity);
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
    _cs2.reserve(capacity);
    _cs3.reserve(capacity);
#endif
  }

#ifdef FFT_UTILS_MUL_INT
  const Complex<T> DOWN_QUART = Complex<T>(0, -0.25);

  template<typename V>
  inline vector<Complex<T>>
  mulInt(const vector<V>& xs, const vector<V>& ys, bool cyclic) {
    if (xs.empty() || ys.empty()) {
      return vector<Complex<T>>(1);
    }
    int pow2 = nextPow2_32(
        cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1);
    vector<Complex<T>> cs(pow2);
    for (size_t i = 0; i < pow2; ++i) {
      cs[i].init(i < xs.size() ? xs[i] : 0, i < ys.size() ? ys[i] : 0);
    }
    fft(cs, false, pow2);
    for (int i = 0; i <= (pow2 >> 1); ++i) {
      int j = (pow2 - i) & (pow2 - 1);
      cs[j] = (cs[i] * cs[i] - (cs[j] * cs[j]).conj()) * DOWN_QUART;
      cs[i].initConj(cs[j]);
    }
    fft(cs, false, pow2);
    for (auto& c : cs) {
      c /= pow2;
    }
    _shrink(cs);
    return cs;
  }
#endif

#ifdef FFT_UTILS_MUL_INLINE_INT
  template<typename V>
  inline void mulInlineInt(vector<V>& xs, const vector<V>& ys, bool cyclic) {
    const auto& cs = mulInt(xs, ys, cyclic);
    xs.resize(cs.size());
    for (size_t i = 0; i < cs.size(); ++i) {
      xs[i] = cs[i].real + 0.5;
    }
    _shrinkInt(xs);
  }
#endif

#ifdef FFT_UTILS_MUL_INLINE_MOD
  const Complex<T> RIGHT_HALF = Complex<T>(0.5, 0);
  const Complex<T> DOWN_HALF = Complex<T>(0, -0.5);
  const Complex<T> UP = Complex<T>(0, 1);

  inline void mulInlineMod(
      vector<int>& xs, const vector<int>& ys, int mod, bool cyclic = false) {
    if (xs.empty() || ys.empty()) {
      xs.clear();
      return;
    }
    int pow2 = nextPow2_32(
        cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1);
    vector<Complex<T>> as(pow2);
    for (size_t i = 0; i < xs.size(); ++i) {
      as[i].init(xs[i] >> 15, xs[i] & 32767);
    }
    fft(as, false, pow2);
    vector<Complex<T>> bs(pow2);
    for (size_t i = 0; i < ys.size(); ++i) {
      bs[i].init(ys[i] >> 15, ys[i] & 32767);
    }
    fft(bs, false, pow2);
    vector<Complex<T>> cs(pow2), ds(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = (pow2 - 1) & (pow2 - i);
      Complex<T> v1 = (as[i] + as[j].conj()) * RIGHT_HALF;
      Complex<T> v2 = (as[i] - as[j].conj()) * DOWN_HALF;
      Complex<T> v3 = (bs[i] + bs[j].conj()) * RIGHT_HALF;
      Complex<T> v4 = (bs[i] - bs[j].conj()) * DOWN_HALF;
      cs[j] = v1 * v3 + v2 * v4 * UP;
      ds[j] = v1 * v4 + v2 * v3;
    }
    fft(cs, false, pow2);
    fft(ds, false, pow2);
    _expand(xs, pow2);
    for (int i = 0; i < pow2; ++i) {
      int64_t v1 = static_cast<int64_t>(cs[i].real / pow2 + 0.5) % mod;
      int64_t v2 = static_cast<int64_t>(ds[i].real / pow2 + 0.5) % mod;
      int64_t v3 = static_cast<int64_t>(cs[i].imag / pow2 + 0.5) % mod;
      xs[i] = ((((v1 << 15) + v2) << 15) + v3) % mod;
    }
    _shrinkInt(xs);
  }
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
  inline void
  mul(vector<Complex<T>>& x,
      vector<Complex<T>>& y,
      vector<Complex<T>>& res,
      bool shrink = false) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    fft(x, false, pow2);
    fft(y, false, pow2);
    res.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      res[i].initMul(x[i], y[i]);
    }
    fft(res, true, pow2);
    if (shrink) {
      _shrink(res);
    }
  }
#endif

#ifdef FFT_UTILS_MUL_INLINE_COMPLEX_VECTOR
  inline void
  mulInline(vector<Complex<T>>& x, vector<Complex<T>>& y, bool shrink = false) {
    if (x.empty() || y.empty()) {
      x.clear();
      return;
    }
    int pow2 = nextPow2_32(x.size() + y.size() - 1);
    fft(x, false, pow2);
    fft(y, false, pow2);
    for (int i = 0; i < pow2; ++i) {
      x[i] *= y[i];
    }
    fft(x, true, pow2);
    if (shrink) {
      _shrink(x);
    }
  }
#endif

#ifdef FFT_UTILS_MUL_INLINE_COMPLEX_MATRIX
  inline void mulInline(
      vector<vector<Complex<T>>>& x,
      vector<vector<Complex<T>>>& y,
      bool cyclic = false) {
    if (x.empty() || y.empty() || x[0].empty() || y[0].empty()) {
      x.clear();
      return;
    }
    int n = cyclic ? max(max(x.size(), y.size()), max(x[0].size(), y[0].size()))
                   : max(x.size() + y.size(), x[0].size() + y[0].size()) - 1;
    int pow2 = nextPow2_32(n);
    fft(x, false, pow2);
    fft(y, false, pow2);
    for (int i = 0; i < pow2; ++i) {
      for (int j = 0; j < pow2; ++j) {
        x[i][j] *= y[i][j];
      }
    }
    fft(x, true, pow2);
  }
#endif

#ifdef FFT_UTILS_ONLINE_MOD
  // f(i)=transform(sum(f(j)*g(i-j), j from 0 to i-1))
  //
  // f(i), 0<=i<computedBound are precomputed
  template<typename V, typename V_SQR, V MOD>
  inline void onlineMod(
      vector<ModInt<V, V_SQR, MOD>>& fs,
      const vector<ModInt<V, V_SQR, MOD>>& gs,
      int mod,
      int computedBound,
      int toComputeBound,
      const function<void(int& f, int idx)>& transform) {
    vector<int> fsI(toComputeBound);
    for (int i = min(toComputeBound, static_cast<int>(fs.size())) - 1; i >= 0;
         --i) {
      fsI[i] = fs[i]._v;
    }
    vector<int> gsI(gs.size());
    for (size_t i = 0; i < gs.size(); ++i) {
      gsI[i] = gs[i]._v;
    }
    _onlineModInt(fsI, gsI, mod, computedBound, 0, toComputeBound, transform);
    if (fs.size() < toComputeBound) {
      fs.resize(toComputeBound);
    }
    for (int i = computedBound; i < toComputeBound; ++i) {
      fs[i] = fsI[i];
    }
  }
#endif

#ifdef FFT_UTILS_ONLINE_MOD_INT
  // f(i)=transform(sum(f(j)*g(i-j), j from 0 to i-1))
  //
  // f(i), 0<=i<computedBound are precomputed
  inline void onlineModInt(
      vector<int>& fs,
      const vector<int>& gs,
      int mod,
      int computedBound,
      int toComputeBound,
      const function<void(int& f, int idx)>& transform) {
    _expand(fs, toComputeBound);
    _onlineModInt(fs, gs, mod, computedBound, 0, toComputeBound, transform);
  }

  inline void _onlineModInt(
      vector<int>& fs,
      const vector<int>& gs,
      int mod,
      int computedBound,
      int lower,
      int upper,
      const function<void(int& f, int idx)>& transform) {
    if (lower + 1 == upper) {
      if (lower >= computedBound) {
        transform(fs[lower], lower);
      }
      return;
    }
    int medium = (lower + upper) >> 1;
    _onlineModInt(fs, gs, mod, computedBound, lower, medium, transform);
    size_t pow2 = nextPow2_32(upper - lower);
    vector<int> delta(pow2);
    for (int i = lower; i < medium; ++i) {
      delta[i - lower] = fs[i];
    }
    vector<int> tmpGs(pow2);
    for (int i = min(pow2, gs.size()) - 1; i >= 0; --i) {
      tmpGs[i] = gs[i];
    }
    mulInlineMod(delta, tmpGs, mod, true);
    for (int i = medium; i < upper; ++i) {
      fs[i] += delta[i - lower];
      if (fs[i] >= mod) {
        fs[i] -= mod;
      }
    }
    _onlineModInt(fs, gs, mod, computedBound, medium, upper, transform);
  }
#endif

#ifdef FFT_UTILS_FFT_COMPLEX_MATRIX
  inline void fft(vector<vector<Complex<T>>>& cs, bool invert, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? cs.size() : n);
    cs.reserve(pow2);
    for (size_t i = 0; i < pow2; ++i) {
      if (i < cs.size()) {
        fft(cs[i], invert, pow2);
      } else {
        cs.push_back(vector<Complex<T>>(pow2));
      }
    }
    for (int i = 0; i < pow2; ++i) {
      for (int j = i + 1; j < pow2; ++j) {
        swap(cs[i][j], cs[j][i]);
      }
    }
    for (size_t i = 0; i < pow2; ++i) {
      fft(cs[i], invert, pow2);
    }
  }
#endif

  inline void fft(vector<Complex<T>>& cs, bool invert, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? cs.size() : n);
    _initCapacity(pow2);
    _expand(cs, pow2);
    if (invert) {
      reverse(cs.begin() + 1, cs.begin() + pow2);
      for (int i = 0; i < pow2; ++i) {
        cs[i] /= pow2;
      }
    }
    int shift = __builtin_ctz(_revs.size()) - __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = _revs[i] >> shift;
      if (i < j) {
        swap(cs[i], cs[j]);
      }
    }
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0, l2 = l << 1; i < pow2; i += l2) {
        for (int j = 0, k = l; j < l; ++j, ++k) {
          Complex<T> c = cs[i + j + l] * _roots[k];
          cs[i + j + l].initSub(cs[i + j], c);
          cs[i + j] += c;
        }
      }
    }
  }

#ifdef _FFT_UTILS_EXPAND_INT_VECTOR
  inline void _expand(vector<int>& xs, int pow2) {
    for (size_t i = xs.size(); i < pow2; ++i) {
      xs.push_back(0);
    }
  }
#endif

  inline void _expand(vector<Complex<T>>& cs, int pow2) {
    for (size_t i = cs.size(); i < pow2; ++i) {
      cs.emplace_back(0, 0);
    }
  }

#ifdef _FFT_UTILS_SHRINK_INT_VECTOR
  template<typename V>
  inline void _shrinkInt(vector<V>& cs) {
    for (; cs.size() > 1 && !cs.back(); cs.pop_back()) {}
  }
#endif

#ifdef _FFT_UTILS_SHRINK_COMPLEX_VECTOR
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
    _roots.resize(pow2);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      T baseAngle = PI / i;
      for (int j = i, k = 1; j < i << 1; j += 2, k += 2) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1].initPolar(1, baseAngle * k);
      }
    }
  }

  vector<int> _revs;
  vector<Complex<T>> _roots;
#ifdef _FFT_UTILS_COMPLEX_VECTOR_3
  vector<Complex<T>> _cs2, _cs3;
#endif
};

} // namespace math
