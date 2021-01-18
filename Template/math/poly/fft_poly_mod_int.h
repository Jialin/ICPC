// ALL FFT_POLY_MOD_INT_ALL
#pragma once

#include "math/fft/fft_mul_mod_utils_macros.h" // INCLUDE
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/fft/fft_mul_mod_utils.h"

namespace math {

template<typename FFT_T, typename V, typename V_SQR, V PRIME>
struct FFTPolyModInt : public vector<ModInt<V, V_SQR, PRIME>> {
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
    FFTMulModUtils<FFT_T>::instance().mulInlineModInt(*this, o);
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
  return "FFTPolyModInt<" + totype(FFT_T()) + "," + totype(V()) + "," +
         totype(V_SQR()) + "," + tostring(PRIME) + ">";
}
#endif
