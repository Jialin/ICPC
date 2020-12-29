#pragma once

#include "math/fft/ntt_utils_prime_macros.h"

#include "math/bit/next_pow2_32.h"
#include "math/mod/add.h"
#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/inv.h"
#include "math/mod/mul.h"
#include "math/mod/mul_inline.h"
#include "math/mod/sub.h"

using namespace std;

namespace math {

////////////////////////////////
// Example setups:
// |prime mod|root|  format   |
// | 7340033 | 5  | (7<<20)+1 |
// |998244353| 31 |(119<<23)+1|
////////////////////////////////
template<typename V = int, typename V_SQR = int64_t>
struct NTTUtilsPrime {
  inline NTTUtilsPrime(V primeMod, V root, int capacity = -1) {
    init(primeMod, root, capacity);
  }

  inline void init(V primeMod, V root, int capacity = -1) {
    _mod = primeMod;
    _root = root;
    _invRoot = invMod(root, _mod);
    _rootPow = 1 << __builtin_ctz(_mod - 1);
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
    _roots[0] = 0;
    _roots[1] = 1;
    _initCapacity(capacity);
    _vs.reserve(capacity);
  }

#ifdef NTT_UTILS_PRIME_MUL_MODIFY
  inline const vector<V>& mulModify(vector<V>& x, vector<V>& y) {
    int pow2 = nextPow2_32(max(static_cast<int>(x.size() + y.size()) - 1, 1));
    _fix(x);
    ntt(x, false, pow2);
    _fix(y);
    ntt(y, false, pow2);
    _vs.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      _vs[i] = mulMod<V, V_SQR>(x[i], y[i], _mod);
    }
    ntt(_vs, true, pow2);
    _shrink(_vs);
    return _vs;
  }

  inline void _fix(vector<V>& x) {
    for (size_t i = 0; i < x.size(); ++i) {
      fixModInline<V>(x[i], _mod);
    }
  }

  inline void _shrink(vector<V>& vs) {
    for (; vs.size() > 1 && !vs.back(); vs.pop_back()) {}
  }
#endif

  inline void ntt(vector<V>& vs, bool invert, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? vs.size() : n);
    _initCapacity(pow2);
    _expand(vs, pow2);
    if (invert) {
      reverse(vs.begin() + 1, vs.begin() + pow2);
      int invPow2 = invMod<V>(pow2, _mod);
      for (int i = 0; i < pow2; ++i) {
        mulModInline<V, V_SQR>(vs[i], invPow2, _mod);
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
          V v = mulMod<V, V_SQR>(vs[i + j + l], _roots[j + l], _mod);
          vs[i + j + l] = subMod<V>(vs[i + j], v, _mod);
          vs[i + j] = addMod<V>(vs[i + j], v, _mod);
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
      V v = expMod<V, V_SQR>(_root, (_rootPow >> 1) / i, _mod),
        mul = mulMod<V, V_SQR>(v, v, _mod);
      for (int j = i; j < i << 1; j += 2) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1] = v;
        mulModInline<V, V_SQR>(v, mul, _mod);
      }
    }
  }

  inline void _expand(vector<V>& vs, int pow2) {
    for (size_t i = vs.size(); i < pow2; ++i) {
      vs.push_back(0);
    }
  }

  vector<V> _revs, _roots, _vs;
  V _mod, _root, _invRoot;
  int _rootPow;
};

} // namespace math
