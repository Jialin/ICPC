// !macro_gen
// ALL FFT_MUL_MOD_UTILS_ALL
#pragma once

#ifdef _FFT_MUL_MOD_UTILS_MOD_INT
// _FFT_MUL_MOD_UTILS_MOD_INT => INCLUDE math/mod/mod_int_macros.h
#include "math/mod/mod_int_macros.h"
#endif

#include "math/fft/fft_mul_mod_utils_macros.h"
#include "math/fft/fft_utils_macros.h" // INCLUDE

#include "math/bit/next_pow2_32.h"
#include "math/complex/complex.h"
#include "math/fft/fft_utils.h"

#ifdef _FFT_MUL_MOD_UTILS_MOD_INT
#include "math/mod/mod_int.h"
#endif

using namespace std;

namespace math {

template<typename T = double>
struct FFTMulModUtils {
  inline static FFTMulModUtils& instance() {
    static FFTMulModUtils instance;
    return instance;
  }

#ifdef FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT // ^
  // FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT => _FFT_MUL_MOD_UTILS_MOD_INT
  template<typename V, typename V_SQR, V MOD>
  inline void mulInlineModInt(
      vector<ModInt<V, V_SQR, MOD>>& xs, const vector<ModInt<V, V_SQR, MOD>>& ys, bool cyclic) {
    if (xs.empty() || ys.empty()) {
      xs.clear();
      return;
    }
    int n = cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1;
    int pow2 = nextPow2_32(n);
    static vector<Complex<T>> as, bs, cs, ds;
    as.resize(pow2);
    for (size_t i = 0; i < xs.size(); ++i) {
      as[i].init(xs[i]._v >> 15, xs[i]._v & 32767);
    }
    for (size_t i = xs.size(); i < pow2; ++i) {
      as[i].init(0, 0);
    }
    bs.resize(pow2);
    for (size_t i = 0; i < ys.size(); ++i) {
      bs[i].init(ys[i]._v >> 15, ys[i]._v & 32767);
    }
    for (size_t i = ys.size(); i < pow2; ++i) {
      bs[i].init(0, 0);
    }
    auto& fft = FFTUtils<T>::instance();
    fft.fft(as, false, pow2);
    fft.fft(bs, false, pow2);
    cs.resize(pow2);
    ds.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = (pow2 - 1) & (pow2 - i);
      // FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT => COMPLEX_ADD
      // FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT => COMPLEX_CONJ
      Complex<T> v1 = as[i] + as[j].conj();
      v1 /= 2;
      // FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT => COMPLEX_SUB
      Complex<T> v2 = as[i] - as[j].conj();
      v2 /= 2;
      swap(v2.real, v2.imag);
      v2.imag = -v2.imag;
      Complex<T> v3 = bs[i] + bs[j].conj();
      v3 /= 2;
      Complex<T> v4 = bs[i] - bs[j].conj();
      v4 /= 2;
      swap(v4.real, v4.imag);
      v4.imag = -v4.imag;
      cs[j] = v2 * v4;
      swap(cs[j].real, cs[j].imag);
      cs[j].real = -cs[j].real;
      cs[j] += v1 * v3;
      ds[j] = v1 * v4 + v2 * v3;
    }
    fft.fft(cs, false, pow2);
    fft.fft(ds, false, pow2);
    if (xs.size() < n) {
      xs.resize(n);
    }
    for (int i = 0; i < n; ++i) {
      int64_t v1 = static_cast<int64_t>(cs[i].real / pow2 + 0.5) % MOD;
      int64_t v2 = static_cast<int64_t>(ds[i].real / pow2 + 0.5) % MOD;
      int64_t v3 = static_cast<int64_t>(cs[i].imag / pow2 + 0.5) % MOD;
      xs[i] = (((v1 << 15) + v2) << 15) + v3;
    }
  }
#endif
};

} // namespace math
