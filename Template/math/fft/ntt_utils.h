// !macro_gen
// ALL NTT_UTILS_ALL
#pragma once

#include "common/macros.h"
#include "math/fft/ntt_utils_macros.h"
#include "math/mod/mod_int_macros.h" // INCLUDE

#include "math/bit/next_pow2_32.h"
#include "math/mod/mod_int.h"

using namespace std;

namespace math {

////////////////////////////////
// Example setups:
// |  mod    |root|  format   |
// | 7340033 | 5  | (7<<20)+1 |
// |924844033|3597|(441<<21)+1|
// |998244353| 31 |(119<<23)+1|
////////////////////////////////
// => MOD_INT_TYPEDEF_V
template<typename MOD_INT, typename MOD_INT::V ROOT>
struct NTTUtils {
  inline static NTTUtils& instance() {
#ifdef LOCAL
    int _rootPow = 1 << __builtin_ctz(MOD_INT::MOD - 1);
    if (ROOT < 0 || MOD_INT(ROOT).exp(_rootPow)._v != 1 ||
        MOD_INT(ROOT).exp(_rootPow >> 1)._v == 1) {
      DEBUGF(
          "Invalid ROOT(%d). PRIME %d = (%d << %d) + 1. Computing the right "
          "one ...\n",
          ROOT,
          MOD_INT::MOD,
          (MOD_INT::MOD - 1) / _rootPow,
          __builtin_ctz(MOD_INT::MOD - 1));
      for (V root = 2;; ++root) {
        if (MOD_INT(root).exp(_rootPow)._v == 1 && MOD_INT(root).exp(_rootPow >> 1)._v != 1) {
          DEBUGF("!!! Set ROOT as %d !!!\n", root);
          assert(false);
        }
      }
    }
#endif
    static NTTUtils instance;
    return instance;
  }

  inline void initCapacity(int capacity) {
    if (_revs.size() >= capacity) {
      return;
    }
    // => MOD_INT_CONST_MOD
    int _rootPow = 1 << __builtin_ctz(MOD_INT::MOD - 1);
    int pow2 = nextPow2_32(max(capacity, 2));
    DEBUG_GE(_rootPow, pow2);
    _revs.reserve(pow2);
    _roots.reserve(pow2);
    if (_revs.size() < 2) {
      _revs.resize(2);
      _revs[0] = 0;
      _revs[1] = 1;
      _roots.resize(2);
      _roots[0] = 0;
      _roots[1] = 1;
    }
    int oldPow2 = _revs.size(), lgN = __builtin_ctz(pow2);
    _revs.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      _revs[i] = (_revs[i >> 1] >> 1) + ((i & 1) << (lgN - 1));
    }
    _roots.resize(pow2);
    MOD_INT root(ROOT);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      // => MOD_INT_TYPEDEF_V_SQR
      // => MOD_INT_EXP
      typename MOD_INT::V_SQR v = root.exp((_rootPow / i) >> 1)._v;
      for (int j = i; j < i << 1; j += 2) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1] = _roots[j] * v % MOD_INT::MOD;
      }
    }
    _quota =
        numeric_limits<uint64_t>::max() / MOD_INT::MOD / *max_element(_roots.begin(), _roots.end());
  }

#ifdef NTT_UTILS_NTT_MOD_INT // ^
  // NTT_UTILS_NTT_MOD_INT => _NTT_UTILS_MOD_INT
  inline void nttModInt(vector<MOD_INT>& vs, bool inverse, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? vs.size() : n);
    static vector<typename MOD_INT::V> vsI;
    vsI.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      vsI[i] = i < vs.size() ? vs[i]._v : 0;
    }
    ntt(vsI, inverse, pow2);
    if (vs.size() < pow2) {
      vs.resize(pow2);
    }
    for (int i = 0; i < pow2; ++i) {
      vs[i] = vsI[i];
    }
  }
#endif

  inline void ntt(vector<typename MOD_INT::V>& vs, bool inverse, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? vs.size() : n);
    initCapacity(pow2);
    static vector<uint64_t> vs64;
    vs64.resize(pow2);
    int shift = __builtin_ctz(_revs.size()) - __builtin_ctz(pow2);
    if (inverse) {
      reverse(vs.begin() + 1, vs.begin() + pow2);
      // => MOD_INT_INV
      typename MOD_INT::V_SQR v = MOD_INT(pow2).inv()._v;
      for (int i = 0; i < pow2; ++i) {
        vs64[i] = vs[_revs[i] >> shift] * v % MOD_INT::MOD;
      }
    } else {
      for (int i = 0; i < pow2; ++i) {
        vs64[i] = vs[_revs[i] >> shift];
      }
    }
    for (int l = 1, cnt = 0; l < pow2; l <<= 1, ++cnt) {
      for (int i = 0; i < pow2; i += l << 1) {
        for (int j = 0; j < l; ++j) {
          uint64_t v = vs64[i + j + l] * _roots[j + l] % MOD_INT::MOD;
          vs64[i + j + l] = MOD_INT::MOD - v + vs64[i + j];
          vs64[i + j] += v;
        }
      }
      if (cnt == _quota) {
        FOR(i, 0, pow2) {
          vs64[i] %= MOD_INT::MOD;
        }
        cnt = 0;
      }
    }
    if (vs.size() < pow2) {
      vs.resize(pow2);
    }
    FOR(i, 0, pow2) {
      vs[i] = vs64[i] % MOD_INT::MOD;
    }
  }

  template<typename T>
  inline void _expand(vector<T>& vs, int pow2) {
    int size = vs.size();
    vs.resize(pow2);
    for (size_t i = size; i < pow2; ++i) {
      vs[i] = 0;
    }
  }

  vector<int> _revs;
  vector<typename MOD_INT::V_SQR> _roots;
  uint64_t _quota;
};

} // namespace math
