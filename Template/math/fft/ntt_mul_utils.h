// !macro_gen
// ALL NTT_MUL_UTILS_ALL
#pragma once

#include "common/macros.h"

#ifdef _NTT_MUL_UTILS_MOD_INT
// _NTT_MUL_UTILS_MOD_INT => INCLUDE math/mod/mod_int_macros.h
#include "math/mod/mod_int_macros.h"
#endif

#include "math/fft/ntt_utils_macros.h" // INCLUDE

#ifdef _NTT_MUL_UTILS_MOD_INT
#include "math/mod/mod_int.h"
#endif

#include "math/bit/next_pow2_32.h"
#include "math/fft/ntt_utils.h"

using namespace std;

namespace math {

template<typename V, typename V_SQR, V PRIME, V ROOT>
struct NTTMulUtils {
#ifdef _NTT_MUL_UTILS_MOD_INT
  using _ModInt = ModInt<V, V_SQR, PRIME>;
#endif

  inline static NTTMulUtils& instance() {
    static NTTMulUtils instance;
    return instance;
  }

#ifdef NTT_MUL_UTILS_MUL_INLINE_MOD_INT // ^
  // NTT_MUL_UTILS_MUL_INLINE_MOD_INT => _NTT_MUL_UTILS_MOD_INT
  inline void mulInlineModInt(vector<_ModInt>& xs, const vector<_ModInt>& ys, bool cyclic) {
    if (xs.empty() || ys.empty()) {
      xs.assign(1, 0);
      return;
    }
    bool isSame = xs.size() == ys.size();
    if (isSame) {
      FORSIZE(i, xs) {
        if (xs[i]._v != ys[i]._v) {
          isSame = false;
          break;
        }
      }
    }
    int pow2 = nextPow2_32(cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1);
    auto& ntt = NTTUtils<V, V_SQR, PRIME, ROOT>::instance();
    static vector<_ModInt> ys2;
    if (!isSame) {
      ys2.resize(pow2);
      FOR(i, 0, pow2) {
        if (i < SIZE(ys)) {
          ys2[i] = ys[i];
        } else {
          ys2[i] = 0;
        }
      }
      ntt.nttModInt(ys2, false, pow2);
    }
    ntt._expand(xs, pow2);
    // NTT_MUL_UTILS_MUL_INLINE_MOD_INT => NTT_UTILS_NTT_MOD_INT
    ntt.nttModInt(xs, false, pow2);
    for (int i = 0; i < pow2; ++i) {
      // NTT_MUL_UTILS_MUL_INLINE_MOD_INT => MOD_INT_MUL_INLINE
      xs[i] *= isSame ? xs[i] : ys2[i];
    }
    ntt.nttModInt(xs, true, pow2);
    _shrinkModInt(xs);
  }

  inline void _shrinkModInt(vector<_ModInt>& vs) {
    for (; vs.size() > 1 && !vs.back()._v; vs.pop_back()) {}
  }
#endif
};

} // namespace math
