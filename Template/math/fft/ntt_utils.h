// ALL NTT_UTILS_ALL
#pragma once

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
template<typename V, typename V_SQR, V PRIME, V ROOT>
struct NTTUtils {
  using _ModInt = ModInt<V, V_SQR, PRIME>;

  inline static NTTUtils& instance() {
#ifdef LOCAL
    int _rootPow = 1 << __builtin_ctz(PRIME - 1);
    if (ROOT < 0 || _ModInt(ROOT).exp(_rootPow)._v != 1 ||
        _ModInt(ROOT).exp(_rootPow >> 1)._v == 1) {
      DEBUGF(
          "Invalid ROOT(%d). PRIME %d = (%d << %d) + 1. Computing the right "
          "one ...\n",
          ROOT,
          PRIME,
          (PRIME - 1) / _rootPow,
          __builtin_ctz(PRIME - 1));
      for (V root = 2;; ++root) {
        if (_ModInt(root).exp(_rootPow)._v == 1 &&
            _ModInt(root).exp(_rootPow >> 1)._v != 1) {
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
    int _rootPow = 1 << __builtin_ctz(PRIME - 1);
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
    _ModInt root(ROOT);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      // => MOD_INT_EXP
      V v = root.exp((_rootPow / i) >> 1)._v;
      for (int j = i; j < i << 1; j += 2) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1] = _roots[j] * v % PRIME;
      }
    }
  }

// ^ NTT_UTILS_NTT_MOD_INT
#ifdef NTT_UTILS_NTT_MOD_INT
  // NTT_UTILS_NTT_MOD_INT => _NTT_UTILS_MOD_INT
  inline void nttModInt(vector<_ModInt>& vs, bool inverse, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? vs.size() : n);
    static vector<V> vsI;
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

  inline void ntt(vector<V>& vs, bool inverse, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? vs.size() : n);
    initCapacity(pow2);
    _expand(vs, pow2);
    if (inverse) {
      reverse(vs.begin() + 1, vs.begin() + pow2);
      // => MOD_INT_INV
      V_SQR v = _ModInt(pow2).inv()._v;
      for (int i = 0; i < pow2; ++i) {
        vs[i] = vs[i] * v % PRIME;
      }
    }
    int shift = __builtin_ctz(_revs.size()) - __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = _revs[i] >> shift;
      if (i < j) {
        swap(vs[i], vs[j]);
      }
    }
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0; i < pow2; i += l << 1) {
        for (int j = 0; j < l; ++j) {
          V v = vs[i + j + l] * _roots[j + l] % PRIME;
          vs[i + j + l] = vs[i + j] + PRIME - v;
          if (vs[i + j + l] >= PRIME) {
            vs[i + j + l] -= PRIME;
          }
          vs[i + j] += v;
          if (vs[i + j] >= PRIME) {
            vs[i + j] -= PRIME;
          }
        }
      }
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
  vector<V_SQR> _roots;
};

} // namespace math
