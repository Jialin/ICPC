// !macro_gen
// ALL NTT_ONLINE_UTILS_ALL
#pragma once

#include "math/fft/ntt_mul_utils_macros.h" // INCLUDE
#include "math/fft/ntt_online_utils_macros.h"
#include "math/mod/mod_int_macros.h" // INCLUDE

#include "common/macros.h"
#include "math/fft/ntt_mul_utils.h"

#ifdef _NTT_ONLINE_UTILS_MOD_INT
#include "math/mod/mod_int.h"
#endif

using namespace std;

namespace math {

// Computes f[i], computedBound<=i<toComputeBound, where
// - f[i]=sum(f[j]*g[i-j], 0<=j<i)
// - 0<=i<computedBound, f[i] is computed
template<typename V, typename V_SQR, V PRIME, V ROOT>
struct NTTOnlineUtils {
#ifdef _NTT_ONLINE_UTILS_MOD_INT
  using _ModInt = ModInt<V, V_SQR, PRIME>;
#endif

  inline static NTTOnlineUtils& instance() {
    static NTTOnlineUtils instance;
    return instance;
  }

#ifdef NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT // ^
  // NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT => _NTT_ONLINE_UTILS_MOD_INT
  inline void onlineInlineModInt(
      vector<_ModInt>& fs,
      const vector<_ModInt>& gs,
      int computedBound,
      int toComputeBound,
      const function<void(_ModInt& f, int idx)>& transform) {
    if (fs.size() < toComputeBound) {
      int n = fs.size();
      fs.resize(toComputeBound);
      FOR(i, n, toComputeBound) {
        fs[i] = 0;
      }
    }
    static vector<_ModInt> gsCopy;
    gsCopy = gs;
    _onlineInlineModInt(fs, gsCopy, computedBound, 0, toComputeBound, transform);
  }

  inline void _onlineInlineModInt(
      vector<_ModInt>& fs,
      const vector<_ModInt>& gs,
      int computedBound,
      int lower,
      int upper,
      const function<void(_ModInt& f, int idx)>& transform) {
    if (lower + 1 == upper) {
      if (lower >= computedBound) {
        transform(fs[lower], lower);
      }
      return;
    }
    int medium = (lower + upper) >> 1;
    _onlineInlineModInt(fs, gs, computedBound, lower, medium, transform);
    size_t pow2 = nextPow2_32(upper - lower);
    static vector<_ModInt> delta;
    delta.assign(pow2, 0);
    FOR(i, lower, medium) {
      delta[i - lower] = fs[i];
    }
    static vector<_ModInt> tmpGs;
    tmpGs.assign(pow2, 0);
    for (int i = min(pow2, gs.size()) - 1; i >= 0; --i) {
      tmpGs[i] = gs[i];
    }
    // NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(delta, tmpGs, true);
    for (int i = medium; i < upper; ++i) {
      // NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT => MOD_INT_ADD_INLINE
      fs[i] += delta[i - lower];
    }
    _onlineInlineModInt(fs, gs, computedBound, medium, upper, transform);
  }
#endif
};

} // namespace math
