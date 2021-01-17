// ALL NTT_POLY_MOD_INT_ALL
#pragma once

#include "math/fft/ntt_mul_utils_macros.h" // INCLUDE
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "math/fft/ntt_mul_utils.h"

namespace math {

template<typename V, typename V_SQR, V PRIME, V ROOT>
struct NTTPolyModInt : public vector<ModInt<V, V_SQR, PRIME>> {
// ^ NTT_POLY_MOD_INT_ASSIGN_VECTOR
#ifdef NTT_POLY_MOD_INT_ASSIGN_VECTOR
  template<typename OV>
  inline void operator=(const vector<OV>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

// ^ NTT_POLY_MOD_INT_MUL_INLINE
#ifdef NTT_POLY_MOD_INT_MUL_INLINE
  inline void operator*=(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(
        *this, o, false);
  }
#endif

// ^ NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
#ifdef NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
  inline void mulInlineCyclic(const NTTPolyModInt& o) {
    // NTT_POLY_MOD_INT_MUL_INLINE => NTT_MUL_UTILS_MUL_INLINE_MOD_INT
    NTTMulUtils<V, V_SQR, PRIME, ROOT>::instance().mulInlineModInt(
        *this, o, true);
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
  return "NTTPolyModInt<" + totype(V()) + "," + totype(V_SQR()) + "," +
         tostring(PRIME) + "," + tostring(ROOT) + ">";
}
#endif
