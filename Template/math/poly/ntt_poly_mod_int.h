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

// => MOD_INT_TYPEDEF_V
template<typename MOD_INT, typename MOD_INT::V ROOT>
struct NTTPolyModInt : public vector<MOD_INT> {
#ifdef NTT_POLY_MOD_INT_CONSTRUCT // ^
  inline NTTPolyModInt(int size = 0, typename MOD_INT::V v = 0) {
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
    NTTMulUtils<MOD_INT, ROOT>::instance().mulInlineModInt(*this, o, false);
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
    // NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < invRevO.size()) {
      this->assign(1, 0);
      return;
    }
    // NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_ASSIGN
    int size = this->size() - invRevO.size() + 1;
    reverse(this->begin(), this->end());
    this->resize(size);
    static NTTPolyModInt tmpO;
    tmpO.resize(size);
    FOR(i, 0, size) {
      tmpO[i] = invRevO[i];
    }
    // NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED => NTT_POLY_MOD_INT_MUL_INLINE
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
    int shift = (a.size() + b.size() - 1) & mask;
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
    // NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<MOD_INT, ROOT>::instance().mulInlineModInt(*this, o, true);
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
      const function<void(MOD_INT& f, int idx)>& transform) {
    // NTT_POLY_MOD_INT_ONLINE_INLINE => _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS
    // NTT_POLY_MOD_INT_ONLINE_INLINE => NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT
    NTTOnlineUtils<MOD_INT, ROOT>::instance().onlineInlineModInt(
        *this, o, computedBound, toComputeBound, transform);
  }
#endif

// Compute k-th element in linear recurrence relations.
//   x_n = coef_0 * x_{n-d} + coef_1 * x_{n-d+1} + ... + coef_{d-1} * x_{n-1}
// Given, x_0, ... x_{d-1}, compute x_k
//
// Reference: https://discuss.codechef.com/t/rng-editorial/10068/5
#ifdef NTT_POLY_MOD_INT_RECURRENCE // ^
  template<typename K>
  inline MOD_INT recurrence(const NTTPolyModInt& xs, K k) const {
    DEBUG_GE(k, 0);
    DEBUG_EQ(this->size(), xs.size());
    int n = this->size();
    if (k < n) {
      return xs[k];
    }
    static NTTPolyModInt qs;
    qs.resize(n + 1);
    qs[0] = 1;
    for (int i = 1, j = n - 1; j >= 0; ++i, --j) {
      qs[i] = (*this)[j];
      // NTT_POLY_MOD_INT_RECURRENCE => MOD_INT_NEGATE_INLINE
      qs[i].negateInline();
    }
    static NTTPolyModInt ps;
    ps = qs;
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_MUL_INLINE
    ps *= xs;
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_TRUNCATE
    ps.truncate(n);
    for (; k > n; k >>= 1) {
      //////////////////////////
      // Compute qs *= qsNegate
      //////////////////////////
      static NTTPolyModInt qsNegate;
      int pow2 = nextPow2_32(max(ps.size(), qs.size()) + qs.size() - 1);
      qsNegate = qs;
      // NTT_POLY_MOD_INT_RECURRENCE => _NTT_POLY_MOD_INT_NTT_UTILS
      auto& ntt = NTTUtils<MOD_INT, ROOT>::instance();
      // NTT_POLY_MOD_INT_RECURRENCE => NTT_UTILS_NTT_MOD_INT
      ntt.nttModInt(qsNegate, false, pow2);
      qs.resize(pow2);
      for (int i = (pow2 >> 1) - 1; i >= 0; --i) {
        // NTT_POLY_MOD_INT_RECURRENCE => MOD_INT_INIT_MUL
        qs[i].initMul(qsNegate[i], qsNegate[i ^ (pow2 >> 1)]);
        qs[i ^ (pow2 >> 1)] = qs[i];
      }
      ntt.nttModInt(qs, true, pow2 >> 1);
      qs.resize(pow2 >> 1);
      // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_SHRINK
      qs.shrink();
      //////////////////////////
      // Compute ps *= qsNegate
      //////////////////////////
      ntt.nttModInt(ps, false, pow2);
      FOR(i, 0, pow2) {
        ps[i] *= qsNegate[i ^ (pow2 >> 1)];
      }
      ntt.nttModInt(ps, true, pow2);
      ps.shrink();
      int idx = 0;
      for (int i = k & 1; i < ps.size(); ++idx, i += 2) {
        ps[idx] = ps[i];
      }
      ps.resize(idx);
    }
    // NTT_POLY_MOD_INT_RECURRENCE => NTT_POLY_MOD_INT_INV_INLINE
    qs.invInline(k + 1);
    ps.truncate(k + 1);
    ps *= qs;
    if (k < ps.size()) {
      return ps[k];
    } else {
      return 0;
    }
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
    static vector<MOD_INT> invs;
    if (invs.size() < this->size() + 1) {
      int n = invs.size();
      invs.resize(this->size() + 1);
      if (SIZE(invs) > 1) {
        invs[1] = 1;
      }
      FOR(i, max(n, 2), SIZE(invs)) {
        // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_CONST_MOD
        invs[i] = invs[MOD_INT::MOD % i];
        // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_MUL_INLINE
        invs[i] *= MOD_INT::MOD / i;
        // NTT_POLY_MOD_INT_INTEGRAL_INLINE => MOD_INT_NEGATE_INLINE
        invs[i].negateInline();
      }
    }
    this->insert(this->begin(), MOD_INT(0));
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
    NTTMulUtils<MOD_INT, ROOT>::instance().mulInlineModInt(*this, invP, false);
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
    auto& ntt = NTTUtils<MOD_INT, ROOT>::instance();
    // _NTT_POLY_MOD_INT_INV => NTT_UTILS_NTT_MOD_INT
    ntt.nttModInt(tmpP, false, pow2);
    ntt.nttModInt(res, false, pow2);
    FOR(i, 0, pow2) {
      typename MOD_INT::V v = res[i]._v;
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
    NTTMulUtils<MOD_INT, ROOT>::instance().mulInlineModInt(res, tmpP, false);
    res.resize(n);
  }
#endif

#ifdef NTT_POLY_MOD_INT_DOT // ^
  inline MOD_INT dot(const NTTPolyModInt& o) const {
    MOD_INT res = 0;
    for (int i = min(SIZE(*this), SIZE(o)) - 1; i >= 0; --i) {
      static MOD_INT subRes;
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

#ifdef NTT_POLY_MOD_INT_TRUNCATE // ^
  inline void truncate(int size) {
    if (this->size() > size) {
      this->resize(size);
    }
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const NTTPolyModInt& vs) {
    o << tostring(static_cast<vector<MOD_INT>>(vs));
    return o;
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename MOD_INT, typename MOD_INT::V ROOT>
inline string totype(const math::NTTPolyModInt<MOD_INT, ROOT>& v) {
  return "NTTPolyModInt<" + totype(MOD_INT::V()) + "," + totype(MOD_INT::V_SQR()) + "," +
         tostring(MOD_INT::PRIME) + "," + tostring(ROOT) + ">";
}
#endif
