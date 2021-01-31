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

#ifdef NTT_POLY_MOD_INT_ASSIGN_VECTOR // ^
  template<typename OV>
  inline void operator=(const vector<OV>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE // ^
  inline void operator*=(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MUL_INLINE => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(*this, o, false);
  }
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC // ^
  inline void mulInlineCyclic(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MUL_INLINE => _NTT_POLY_MOD_INT_NTT_MUL_UTILS
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(*this, o, true);
  }
#endif

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
  inline void invInline() {
    static NTTPolyModInt tmpP;
    int n = this->size();
    tmpP.resize(n);
    FOR(i, 0, n) {
      tmpP[i] = (*this)[i];
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
