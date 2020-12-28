#pragma once

#include "math/fft/ntt_utils_fix_mod_macros.h"

#include "math/bit/next_pow2_32.h"
#include "math/mod/mod_int.h"

using namespace std;

namespace math {

////////////////////////////////
// Example setups:
// |  mod    |root|  format   |
// | 7340033 | 5  | (7<<20)+1 |
// |998244353| 31 |(119<<23)+1|
////////////////////////////////
template<typename V, typename V_SQR, V MOD, V ROOT>
struct NTTUtilsFixMod {
  using _ModInt = ModInt<V, V_SQR, MOD>;

  inline NTTUtilsFixMod(int capacity = -1) {
    init(capacity);
  }

  inline void init(int capacity = -1) {
    _root = _ModInt(ROOT);
    _invRoot = _root.inv();
    _rootPow = 1 << __builtin_ctz(MOD - 1);
    if (capacity > 0) {
      capacity = nextPow2_32(capacity);
    }
    capacity = max(capacity, 2);
    _revs.reserve(capacity);
    _revs.clear();
    _revs.push_back(0);
    _revs.push_back(1);
    _roots.reserve(capacity);
    _roots.clear();
    _roots.emplace_back(0);
    _roots.emplace_back(1);
    _initCapacity(capacity);
  }

#ifdef NTT_UTILS_FIX_MOD_MUL_INLINE
  inline void mulInline(vector<_ModInt>& xs, vector<_ModInt>& ys) {
    int pow2 = nextPow2_32(max(static_cast<int>(xs.size() + ys.size()) - 1, 1));
    _expand(pow2, xs);
    ntt(xs, false, pow2);
    _expand(pow2, ys);
    ntt(ys, false, pow2);
    for (int i = 0; i < pow2; ++i) {
      xs[i] *= ys[i];
    }
    ntt(xs, true, pow2);
    _shrink(xs);
  }

  inline void _shrink(vector<_ModInt>& vs) {
    for (; vs.size() > 1 && !vs.back()._v; vs.pop_back()) {}
  }
#endif

  inline void ntt(vector<_ModInt>& vs, bool invert, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? vs.size() : n);
    _initCapacity(pow2);
    _expand(pow2, vs);
    if (invert) {
      reverse(vs.begin() + 1, vs.begin() + pow2);
      _v = _ModInt(pow2).inv();
      for (int i = 0; i < pow2; ++i) {
        vs[i] *= _v;
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
      for (int i = 0, l2 = l << 1; i < pow2; i += l2) {
        for (int j = 0; j < l; ++j) {
          _v.initMul(vs[i + j + l], _roots[j + l]);
          vs[i + j + l].initSub(vs[i + j], _v);
          vs[i + j] += _v;
        }
      }
    }
  }

  inline void _initCapacity(int pow2) {
    if (_revs.size() >= pow2) {
      return;
    }
    DEBUG_GE(_rootPow, pow2);
    int oldPow2 = _revs.size(), lgN = __builtin_ctz(pow2);
    _revs.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      _revs[i] = (_revs[i >> 1] >> 1) + ((i & 1) << (lgN - 1));
    }
    _roots.resize(pow2);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      _v = _root.exp((_rootPow / i) >> 1);
      for (int j = i; j < i << 1; j += 2) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1].initMul(_roots[j], _v);
      }
    }
  }

  inline void _expand(int pow2, vector<_ModInt>& vs) {
    int size = vs.size();
    vs.resize(pow2);
    for (size_t i = size; i < pow2; ++i) {
      vs[i] = 0;
    }
  }

  vector<int> _revs;
  vector<_ModInt> _roots;
  _ModInt _root, _invRoot, _v;
  int _rootPow;
};

} // namespace math
