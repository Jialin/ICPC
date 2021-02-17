// !macro_gen
// ALL NTT_MUL_UTILS_ALL
#pragma once

#include "common/macros.h"

#include "math/fft/ntt_utils_macros.h" // INCLUDE
#include "math/mod/mod_int_macros.h"

#include "math/bit/next_pow2_32.h"
#include "math/fft/ntt_utils.h"
#include "math/mod/mod_int.h"

using namespace std;

namespace math {

// => MOD_INT_TYPEDEF_V
template<typename MOD_INT, typename MOD_INT::V ROOT>
struct NTTMulUtils {
  inline static NTTMulUtils& instance() {
    static NTTMulUtils instance;
    return instance;
  }

#ifdef NTT_MUL_UTILS_MUL_INLINE_MOD_INT // ^
  inline void mulInlineModInt(vector<MOD_INT>& xs, const vector<MOD_INT>& ys, bool cyclic) {
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
    // NTT_MUL_UTILS_MUL_INLINE_MOD_INT => MOD_INT_TYPEDEF_V_SQR
    // NTT_MUL_UTILS_MUL_INLINE_MOD_INT => MOD_INT_CONST_MOD
    auto& ntt =
        NTTUtils<typename MOD_INT::V, typename MOD_INT::V_SQR, MOD_INT::MOD, ROOT>::instance();
    static vector<MOD_INT> ys2;
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

  inline void _shrinkModInt(vector<MOD_INT>& vs) {
    for (; vs.size() > 1 && !vs.back()._v; vs.pop_back()) {}
  }
#endif
};

} // namespace math
