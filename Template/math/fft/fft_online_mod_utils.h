// !macro_gen
// ALL FFT_ONLINE_MOD_UTILS_ALL
#pragma once

#ifdef _FFT_ONLINE_MOD_UTILS_MOD_INT
// _FFT_ONLINE_MOD_UTILS_MOD_INT => INCLUDE math/mod/mod_int_macros.h
#include "math/mod/mod_int_macros.h"
#endif

#include "math/fft/fft_mul_mod_utils_macros.h" // INCLUDE
#include "math/fft/fft_online_mod_utils_macros.h"

#include "common/macros.h"
#include "math/fft/fft_mul_mod_utils.h"

#ifdef _FFT_ONLINE_MOD_UTILS_MOD_INT
#include "math/mod/mod_int.h"
#endif

using namespace std;

namespace math {

// Computes f[i], computedBound<=i<toComputeBound, where
// - f[i]=sum(f[j]*g[i-j], 0<=j<i)
// - 0<=i<computedBound, f[i] is computed
template<typename T = double>
struct FFTOnlineModUtils {
  inline static FFTOnlineModUtils& instance() {
    static FFTOnlineModUtils instance;
    return instance;
  }

#ifdef FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT // ^
  // FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT => _FFT_ONLINE_MOD_UTILS_MOD_INT
  template<typename V, typename V_SQR, V MOD>
  inline void onlineInlineModInt(
      vector<ModInt<V, V_SQR, MOD>>& fs,
      const vector<ModInt<V, V_SQR, MOD>>& gs,
      int computedBound,
      int toComputeBound,
      const function<void(ModInt<V, V_SQR, MOD>& f, int idx)>& transform) {
    if (fs.size() < toComputeBound) {
      int n = fs.size();
      fs.resize(toComputeBound);
      FOR(i, n, toComputeBound) {
        fs[i] = 0;
      }
    }
    static vector<ModInt<V, V_SQR, MOD>> gsCopy;
    gsCopy = gs;
    _onlineInlineModInt(fs, gsCopy, computedBound, 0, toComputeBound, transform);
  }

  template<typename V, typename V_SQR, V MOD>
  inline void _onlineInlineModInt(
      vector<ModInt<V, V_SQR, MOD>>& fs,
      const vector<ModInt<V, V_SQR, MOD>>& gs,
      int computedBound,
      int lower,
      int upper,
      const function<void(ModInt<V, V_SQR, MOD>& f, int idx)>& transform) {
    if (lower + 1 == upper) {
      if (lower >= computedBound) {
        transform(fs[lower], lower);
      }
      return;
    }
    int medium = (lower + upper) >> 1;
    _onlineInlineModInt(fs, gs, computedBound, lower, medium, transform);
    size_t pow2 = nextPow2_32(upper - lower);
    static vector<ModInt<V, V_SQR, MOD>> delta;
    delta.assign(pow2, 0);
    FOR(i, lower, medium) {
      delta[i - lower] = fs[i];
    }
    static vector<ModInt<V, V_SQR, MOD>> tmpGs;
    tmpGs.assign(pow2, 0);
    for (int i = min(pow2, gs.size()) - 1; i >= 0; --i) {
      tmpGs[i] = gs[i];
    }
    // FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT => FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
    FFTMulModUtils<T>::instance().mulInlineModInt(delta, tmpGs, true);
    for (int i = medium; i < upper; ++i) {
      // FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT => MOD_INT_ADD_INLINE
      fs[i] += delta[i - lower];
    }
    _onlineInlineModInt(fs, gs, computedBound, medium, upper, transform);
  }
#endif
};

} // namespace math
