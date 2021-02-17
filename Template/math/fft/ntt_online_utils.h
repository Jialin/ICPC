// !macro_gen
// ALL NTT_ONLINE_UTILS_ALL
#pragma once

#include "math/mod/mod_int_macros.h"

#include "math/fft/ntt_mul_utils_macros.h" // INCLUDE
#include "math/fft/ntt_online_utils_macros.h"
#include "math/mod/mod_int_macros.h" // INCLUDE

#include "common/macros.h"
#include "math/fft/ntt_mul_utils.h"
#include "math/mod/mod_int.h"

using namespace std;

namespace math {

// Computes f[i], computedBound<=i<toComputeBound, where
// - f[i]=sum(f[j]*g[i-j], 0<=j<i)
// - 0<=i<computedBound, f[i] is computed
//
// => MOD_INT_TYPEDEF_V
template<typename MOD_INT, typename MOD_INT::V ROOT>
struct NTTOnlineUtils {
  inline static NTTOnlineUtils& instance() {
    static NTTOnlineUtils instance;
    return instance;
  }

#ifdef NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT // ^
  inline void onlineInlineModInt(
      vector<MOD_INT>& fs,
      const vector<MOD_INT>& gs,
      int computedBound,
      int toComputeBound,
      const function<void(MOD_INT& f, int idx)>& transform) {
    if (fs.size() < toComputeBound) {
      int n = fs.size();
      fs.resize(toComputeBound);
      FOR(i, n, toComputeBound) {
        fs[i] = 0;
      }
    }
    static vector<MOD_INT> gsCopy;
    gsCopy = gs;
    _onlineInlineModInt(fs, gsCopy, computedBound, 0, toComputeBound, transform);
  }

  inline void _onlineInlineModInt(
      vector<MOD_INT>& fs,
      const vector<MOD_INT>& gs,
      int computedBound,
      int lower,
      int upper,
      const function<void(MOD_INT& f, int idx)>& transform) {
    if (lower + 1 == upper) {
      if (lower >= computedBound) {
        transform(fs[lower], lower);
      }
      return;
    }
    int medium = (lower + upper) >> 1;
    _onlineInlineModInt(fs, gs, computedBound, lower, medium, transform);
    size_t pow2 = nextPow2_32(upper - lower);
    static vector<MOD_INT> delta;
    delta.assign(pow2, 0);
    FOR(i, lower, medium) {
      delta[i - lower] = fs[i];
    }
    static vector<MOD_INT> tmpGs;
    tmpGs.assign(pow2, 0);
    for (int i = min(pow2, gs.size()) - 1; i >= 0; --i) {
      tmpGs[i] = gs[i];
    }
    // NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<MOD_INT, ROOT>::instance().mulInlineModInt(delta, tmpGs, true);
    for (int i = medium; i < upper; ++i) {
      // NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT => MOD_INT_ADD_INLINE
      fs[i] += delta[i - lower];
    }
    _onlineInlineModInt(fs, gs, computedBound, medium, upper, transform);
  }
#endif
};

} // namespace math
