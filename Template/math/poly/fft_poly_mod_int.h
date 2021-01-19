// ALL FFT_POLY_MOD_INT_ALL
#pragma once

#include "math/fft/fft_mul_mod_utils_macros.h"    // INCLUDE
#include "math/fft/fft_online_mod_utils_macros.h" // INCLUDE
#include "math/mod/mod_int_macros.h"
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/mod/mod_int.h"

#ifdef FFT_POLY_MOD_INT_MUL_INLINE
#include "math/fft/fft_mul_mod_utils.h"
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE
#include "math/fft/fft_online_mod_utils.h"
#endif

namespace math {

template<typename FFT_T, typename V, typename V_SQR, V PRIME>
struct FFTPolyModInt : public vector<ModInt<V, V_SQR, PRIME>> {
#ifdef FFT_POLY_MOD_INT_CONSTRUCT // ^
  inline FFTPolyModInt(int size = 0, V v = 0) {
    this->assign(size, v);
  }
#endif

#ifdef FFT_POLY_MOD_INT_ASSIGN_VECTOR // ^
  template<typename OV>
  inline void operator=(const vector<OV>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE // ^
  inline void operator*=(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_MUL_INLINE => FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
    FFTMulModUtils<FFT_T>::instance().mulInlineModInt(*this, o, false);
  }
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE // ^
  inline void onlineInline(
      const FFTPolyModInt& o,
      int computedBound,
      int toComputeBound,
      const function<void(ModInt<V, V_SQR, PRIME>& f, int idx)>& transform) {
    // FFT_POLY_MOD_INT_ONLINE_INLINE => FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT
    FFTOnlineModUtils<FFT_T>::instance().template onlineInlineModInt<V, V_SQR, PRIME>(
        *this, o, computedBound, toComputeBound, transform);
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const FFTPolyModInt& vs) {
    o << tostring(static_cast<vector<ModInt<V, V_SQR, PRIME>>>(vs));
    return o;
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename FFT_T, typename V, typename V_SQR, V PRIME>
inline string totype(const math::FFTPolyModInt<FFT_T, V, V_SQR, PRIME>& v) {
  return "FFTPolyModInt<" + totype(FFT_T()) + "," + totype(V()) + "," + totype(V_SQR()) + "," +
         tostring(PRIME) + ">";
}
#endif
