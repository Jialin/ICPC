// !macro_gen
// ALL NTT_POLY_MOD_INT_ALL
#pragma once

#ifdef _NTT_POLY_MOD_INT_NTT_UTILS
// _NTT_POLY_MOD_INT_NTT_UTILS => INCLUDE math/fft/ntt_utils_macros.h
#include "math/fft/ntt_utils_macros.h"
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_MUL_UTILS
// _NTT_POLY_MOD_INT_NTT_MUL_UTILS => INCLUDE math/fft/ntt_mul_utils_macros.h
#include "math/fft/ntt_mul_utils_macros.h"
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS
// _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS => INCLUDE math/fft/ntt_online_utils_macros.h
#include "math/fft/ntt_online_utils_macros.h"
#endif

#include "math/mod/mod_int_macros.h" // INCLUDE
#include "math/poly/ntt_poly_mod_int_macros.h"

#ifdef _NTT_POLY_MOD_INT_NTT_UTILS
#include "math/fft/ntt_utils.h"
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#include "math/fft/ntt_mul_utils.h"
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS
#include "math/fft/ntt_online_utils.h"
#endif

#include "math/mod/mod_int.h"

namespace math {

template<typename V, typename V_SQR, V PRIME, V ROOT>
struct NTTPolyModInt : public vector<ModInt<V, V_SQR, PRIME>> {
#ifdef NTT_POLY_MOD_INT_CONSTRUCT // ^
  inline NTTPolyModInt(int size = 0, V v = 0) {
    this->assign(size, v);
  }
#endif

#ifdef NTT_POLY_MOD_INT_ASSIGN // ^
  inline void operator=(const NTTPolyModInt& o) {
    this->resize(o.size());
    FORSIZE(i, o) {
      (*this)[i] = o[i];
    }
    shrink();
  }
#endif

#ifdef NTT_POLY_MOD_INT_ASSIGN_VECTOR // ^
  template<typename OV>
  inline void operator=(const vector<OV>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef NTT_POLY_MOD_INT_SUB_INLINE // ^
  inline void operator-=(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_SUB_INLINE => NTT_POLY_MOD_INT_EXTEND
    extend(o.size());
    for (int i = SIZE(o) - 1; i >= 0; --i) {
      // NTT_POLY_MOD_INT_SUB_INLINE => MOD_INT_SUB_INLINE
      (*this)[i] -= o[i];
    }
    // NTT_POLY_MOD_INT_SUB_INLINE => NTT_POLY_MOD_SHRINK
    shrink();
  }
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE // ^
  inline void operator*=(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MUL_INLINE => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(*this, o, false);
  }
#endif

#ifdef NTT_POLY_MOD_INT_DIV_INLINE // ^
  inline void operator/=(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < o.size()) {
      this->assign(1, 0);
      return;
    }
    static NTTPolyModInt tmpO;
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_ASSIGN
    tmpO = o;
    tmpO.shrink();
    int size = this->size() - tmpO.size() + 1;
    reverse(this->begin(), this->end());
    this->resize(size);
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_INV_INLINE
    reverse(tmpO.begin(), tmpO.end());
    tmpO.invInline(size);
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_MUL_INLINE
    *this *= tmpO;
    this->resize(size);
    reverse(this->begin(), this->end());
    shrink();
  }
#endif

#ifdef NTT_POLY_MOD_INT_MOD_INLINE // ^
  inline void operator%=(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MOD_INLINE => NTT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < o.size()) {
      return;
    }
    static NTTPolyModInt tmp;
    // NTT_POLY_MOD_INT_MOD_INLINE => NTT_POLY_MOD_INT_ASSIGN
    tmp = *this;
    // NTT_POLY_MOD_INT_MOD_INLINE => NTT_POLY_MOD_INT_DIV_INLINE
    tmp /= o;
    // NTT_POLY_MOD_INT_MOD_INLINE => NTT_POLY_MOD_INT_MUL_INLINE
    tmp *= o;
    // NTT_POLY_MOD_INT_MOD_INLINE => NTT_POLY_MOD_INT_SUB_INLINE
    *this -= tmp;
  }
#endif

#ifdef NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED // ^
  inline void divInlinePrecomputed(const NTTPolyModInt& invRevO) {
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < invRevO.size()) {
      this->assign(1, 0);
      return;
    }
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_ASSIGN
    int size = this->size() - invRevO.size() + 1;
    reverse(this->begin(), this->end());
    this->resize(size);
    static NTTPolyModInt tmpO;
    tmpO.resize(size);
    FOR(i, 0, size) {
      tmpO[i] = invRevO[i];
    }
    // NTT_POLY_MOD_INT_DIV_INLINE => NTT_POLY_MOD_INT_MUL_INLINE
    *this *= tmpO;
    this->resize(size);
    reverse(this->begin(), this->end());
    shrink();
  }
#endif

#ifdef NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED // ^
  inline void modInlinePrecomputed(const NTTPolyModInt& o, const NTTPolyModInt& invRevO) {
    if (this->size() < invRevO.size()) {
      return;
    }
    static NTTPolyModInt tmp;
    // NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_ASSIGN
    tmp = *this;
    // NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED
    tmp.divInlinePrecomputed(invRevO);
    _subInlineMul(tmp, o);
  }

  inline void _subInlineMul(NTTPolyModInt& a, const NTTPolyModInt& b) {
    int aSize = a.size();
    int mask = nextPow2_32(max(a.size(), b.size())) - 1;
    int shift = ((a.size() + b.size() - 1) & mask);
    // NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
    a.mulInlineCyclic(b);
    // NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_EXTEND
    a.extend(mask + 1);
    for (int i = 0, j = a.size() - 1 + shift; i < aSize; ++i, --j) {
      // NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => MOD_INT_SUB_INLINE
      a[j & mask] -= (*this)[this->size() - 1 - i];
    }
    this->resize(this->size() - aSize);
    int j = a.size() - aSize + shift - this->size();
    if (j < 0) {
      j = j % (mask + 1) + mask + 1;
    }
    j &= mask;
    for (int i = 0; i < this->size(); ++i, ++j) {
      (*this)[i] -= a[j & mask];
    }
  }
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC // ^
  inline void mulInlineCyclic(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MUL_INLINE => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(*this, o, true);
  }
#endif

// Computes f[i], computedBound<=i<toComputeBound, where
// - f[i]=transform(sum(f[j]*g[i-j], 0<=j<i))
// - 0<=i<computedBound, f[i] is computed
#ifdef NTT_POLY_MOD_INT_ONLINE_INLINE // ^
  inline void onlineInline(
      const NTTPolyModInt& o,
      int computedBound,
      int toComputeBound,
      const function<void(ModInt<V, V_SQR, PRIME>& f, int idx)>& transform) {
    // NTT_POLY_MOD_INT_ONLINE_INLINE => _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS
    // NTT_POLY_MOD_INT_ONLINE_INLINE => NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT
    NTTOnlineUtils<V, V_SQR, PRIME, ROOT>::instance().onlineInlineModInt(
        *this, o, computedBound, toComputeBound, transform);
  }
#endif

// Compute k-th element in linear recurrence relations.
//   x_n = coef_0 * x_{n-d} + coef_1 * x_{n-d+1} + ... + coef_{d-1} * x_{n-1}
// Given, x_0, ... x_{d-1}, compute x_k
#ifdef NTT_POLY_MOD_INT_RECURRENCE // ^
  template<typename K>
  inline ModInt<V, V_SQR, PRIME> recurrence(const NTTPolyModInt& xs, K k) const {
    DEBUG_GE(k, 0);
    if (!k) {
      return xs[0];
    }
    static NTTPolyModInt modP;
    int n = this->size();
    modP.resize(n + 1);
    FOR(i, 0, n) {
      modP[i] = (*this)[i];
      // NTT_POLY_MOD_INT_RECURRENCE => MOD_INT_NEGATE_INLINE
      modP[i].negateInline();
    }
    modP[n] = 1;
    static NTTPolyModInt invRevModP;
    invRevModP = modP;
    reverse(invRevModP.begin(), invRevModP.end());
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_INV_INLINE
    invRevModP.invInline();
    static NTTPolyModInt resP;
    resP.resize(2);
    resP[0] = 0;
    resP[1] = 1;
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED
    resP.modInlinePrecomputed(modP, invRevModP);
    resP._recurrence(modP, invRevModP, k);
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_DOT
    return xs.dot(resP);
  }

  template<typename K>
  inline void _recurrence(const NTTPolyModInt& o, const NTTPolyModInt& invRevO, K k) {
    if (k == 1) {
      return;
    }
    _recurrence(o, invRevO, k >> 1);
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_MUL_INLINE
    *this *= *this;
    if (k & 1) {
      this->resize(this->size() + 1);
      for (int i = SIZE(*this) - 1; i > 0; --i) {
        (*this)[i] = (*this)[i - 1];
      }
      (*this)[0] = 0;
    }
    this->modInlinePrecomputed(o, invRevO);
  }
#endif

#ifdef NTT_POLY_MOD_INT_DERIVE_INLINE // ^
  inline void deriveInline() {
    if (this->empty()) {
      return;
    }
    this->erase(this->begin());
    FOR(i, 0, SIZE(*this)) {
      // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_MUL_INLINE
      (*this)[i] *= i + 1;
    }
  }
#endif

#ifdef NTT_POLY_MOD_INT_INTEGRAL_INLINE // ^
  inline void integralInline() {
    if (this->empty()) {
      return;
    }
    static vector<ModInt<V, V_SQR, PRIME>> invs;
    if (invs.size() < this->size() + 1) {
      int n = invs.size();
      invs.resize(this->size() + 1);
      if (SIZE(invs) > 1) {
        invs[1] = 1;
      }
      FOR(i, max(n, 2), SIZE(invs)) {
        invs[i] = invs[PRIME % i];
        // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_MUL_INLINE
        invs[i] *= PRIME / i;
        // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_NEGATE_INLINE
        invs[i].negateInline();
      }
    }
    this->insert(this->begin(), ModInt<V, V_SQR, PRIME>(0));
    FOR(i, 1, SIZE(*this)) {
      // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_MUL_INLINE
      (*this)[i] *= invs[i];
    }
  }
#endif

#ifdef NTT_POLY_MOD_INT_LN_INLINE // ^
  inline void lnInline() {
    if (this->empty()) {
      return;
    }
    DEBUG_EQ((*this)[0]._v, 1);
    static NTTPolyModInt invP;
    int n = this->size();
    invP.resize(n);
    FOR(i, 0, SIZE(invP)) {
      invP[i] = (*this)[i];
    }
    // NTT_POLY_MOD_INT_LN_INLINE => NTT_POLY_MOD_INT_INV_INLINE
    invP.invInline();
    // NTT_POLY_MOD_INT_LN_INLINE => NTT_POLY_MOD_INT_DERIVE_INLINE
    deriveInline();
    // NTT_POLY_MOD_INT_LN_INLINE => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // NTT_POLY_MOD_INT_LN_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(*this, invP, false);
    this->resize(n);
    // NTT_POLY_MOD_INT_LN_INLINE => NTT_POLY_MOD_INT_INTEGRAL_INLINE
    integralInline();
  }
#endif

#ifdef NTT_POLY_MOD_INT_EXP_INLINE // ^
  inline void expInline() {
    // NTT_POLY_MOD_INT_EXP_INLINE => NTT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->empty() || (this->size() == 1 && !(*this)[0]._v)) {
      this->assign(1, 1);
      return;
    }
    static NTTPolyModInt tmpP;
    int n = this->size();
    tmpP.resize(n);
    FOR(i, 0, n) {
      tmpP[i] = (*this)[i];
    }
    // NTT_POLY_MOD_INT_EXP_INLINE => _NTT_POLY_MOD_INT_EXP
    _exp(tmpP, *this, n);
  }
#endif

#ifdef NTT_POLY_MOD_INT_INV // ^
  inline NTTPolyModInt inv() const {
    NTTPolyModInt res = *this;
    if (this->empty()) {
      return res;
    }
    // NTT_POLY_MOD_INT_INV => _NTT_POLY_MOD_INT_INV
    _inv(*this, res, this->size());
    return res;
  }
#endif

#ifdef NTT_POLY_MOD_INT_INV_INLINE // ^
  inline void invInline(int size = -1) {
    static NTTPolyModInt tmpP;
    int n = size < 0 ? this->size() : size;
    tmpP.resize(n);
    FOR(i, 0, n) {
      if (i < this->size()) {
        tmpP[i] = (*this)[i];
      } else {
        tmpP[i] = 0;
      }
    }
    // NTT_POLY_MOD_INT_INV_INLINE => _NTT_POLY_MOD_INT_INV
    _inv(tmpP, *this, n);
  }
#endif

#ifdef _NTT_POLY_MOD_INT_INV
  inline static void _inv(const NTTPolyModInt& p, NTTPolyModInt& res, int n) {
    if (n == 1) {
      DEBUG_GT(p[0]._v, 0);
      res.resize(1);
      // _NTT_POLY_MOD_INT_INV => MOD_INT_INV
      res[0] = p[0].inv();
      return;
    }
    int nHalf = (n + 1) >> 1;
    _inv(p, res, nHalf);
    static NTTPolyModInt tmpP;
    int pow2 = nextPow2_32(n + (nHalf << 1) - 2);
    tmpP.resize(pow2);
    FOR(i, 0, n) {
      tmpP[i] = p[i];
    }
    FOR(i, n, pow2) {
      tmpP[i] = 0;
    }
    // _NTT_POLY_MOD_INT_INV => _NTT_POLY_MOD_INT_NTT_UTILS
    auto& ntt = NTTUtils<V, V_SQR, PRIME, ROOT>::instance();
    // _NTT_POLY_MOD_INT_INV => NTT_UTILS_NTT_MOD_INT
    ntt.nttModInt(tmpP, false, pow2);
    ntt.nttModInt(res, false, pow2);
    FOR(i, 0, pow2) {
      V v = res[i]._v;
      // _NTT_POLY_MOD_INT_INV => MOD_INT_MUL_INLINE
      res[i] *= tmpP[i];
      // _NTT_POLY_MOD_INT_INV => MOD_INT_NEGATE_INLINE
      res[i].negateInline();
      // _NTT_POLY_MOD_INT_INV => MOD_INT_ADD_INLINE
      res[i] += 2;
      res[i] *= v;
    }
    ntt.nttModInt(res, true, pow2);
    res.resize(n);
  }
#endif

#ifdef _NTT_POLY_MOD_INT_EXP
  inline static void _exp(const NTTPolyModInt& p, NTTPolyModInt& res, int n) {
    if (n == 1) {
      DEBUG_EQ(p[0]._v, 0);
      res.resize(1);
      res[0] = 1;
      return;
    }
    int nHalf = (n + 1) >> 1;
    _exp(p, res, nHalf);
    static NTTPolyModInt tmpP;
    tmpP.resize(n);
    FOR(i, 0, nHalf) {
      tmpP[i] = res[i];
    }
    FOR(i, nHalf, n) {
      tmpP[i] = 0;
    }
    // _NTT_POLY_MOD_INT_EXP => NTT_POLY_MOD_INT_LN_INLINE
    tmpP.lnInline();
    tmpP.resize(n);
    FOR(i, 0, n) {
      // _NTT_POLY_MOD_INT_EXP => MOD_INT_INIT_SUB
      tmpP[i].initSub(p[i], tmpP[i]);
    }
    // _NTT_POLY_MOD_INT_EXP => MOD_INT_ADD_INLINE
    tmpP[0] += 1;
    // _NTT_POLY_MOD_INT_EXP => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // _NTT_POLY_MOD_INT_EXP => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(res, tmpP, false);
    res.resize(n);
  }
#endif

#ifdef NTT_POLY_MOD_INT_DOT // ^
  inline ModInt<V, V_SQR, PRIME> dot(const NTTPolyModInt& o) const {
    ModInt<V, V_SQR, PRIME> res = 0;
    for (int i = min(SIZE(*this), SIZE(o)) - 1; i >= 0; --i) {
      static ModInt<V, V_SQR, PRIME> subRes;
      // NTT_POLY_MOD_INT_DOT => MOD_INT_INIT_MUL
      subRes.initMul((*this)[i], o[i]);
      // NTT_POLY_MOD_INT_DOT => MOD_INT_ADD_INLINE
      res += subRes;
    }
    return res;
  }
#endif

#ifdef NTT_POLY_MOD_INT_EXTEND // ^
  inline void extend(int size) {
    for (; this->size() < size; this->emplace_back(0)) {}
  }
#endif

#ifdef NTT_POLY_MOD_INT_SHRINK // ^
  inline void shrink() {
    for (; this->size() > 1 && !this->back()._v; this->pop_back()) {}
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const NTTPolyModInt& vs) {
    o << tostring(static_cast<vector<ModInt<V, V_SQR, PRIME>>>(vs));
    return o;
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename V, typename V_SQR, V PRIME, V ROOT>
inline string totype(const math::NTTPolyModInt<V, V_SQR, PRIME, ROOT>& v) {
  return "NTTPolyModInt<" + totype(V()) + "," + totype(V_SQR()) + "," + tostring(PRIME) + "," +
         tostring(ROOT) + ">";
}
#endif
