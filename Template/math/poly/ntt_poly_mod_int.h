// !macro_gen
// ALL NTT_POLY_MOD_INT_ALL
#pragma once

#ifdef _NTT_POLY_MOD_INT_ONLINE_UTILS
// _NTT_POLY_MOD_INT_ONLINE_UTILS => INCLUDE math/fft/ntt_online_utils_macros.h
#include "math/fft/ntt_online_utils_macros.h"
#endif

#include "math/fft/ntt_mul_utils_macros.h" // INCLUDE
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "math/fft/ntt_mul_utils.h"

#ifdef _NTT_POLY_MOD_INT_ONLINE_UTILS
#include "math/fft/ntt_online_utils.h"
#endif

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
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(*this, o, false);
  }
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC // ^
  inline void mulInlineCyclic(const NTTPolyModInt& o) {
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
    // NTT_POLY_MOD_INT_ONLINE_INLINE => _NTT_POLY_MOD_INT_ONLINE_UTILS
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
      (*this)[i] *= i + 1;
    }
  }
#endif

#ifdef NTT_POLY_MOD_INT_INTEGRAL_INLINE // ^
  inline void integralInline() {
    if (this->empty()) {
      return;
    }
    this->insert(this->begin(), ModInt<V, V_SQR, PRIME>(0));
    FOR(i, 1, SIZE(*this)) {
      (*this)[i] /= i;
    }
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
