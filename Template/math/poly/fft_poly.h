// ALL FFT_POLY_ALL
#pragma once

#include "math/fft/fft_mul_utils_macros.h" // INCLUDE
#include "math/poly/fft_poly_macros.h"

#include "math/fft/fft_mul_utils.h"

namespace math {

template<typename V, typename FFT_T = long double>
struct FFTPoly : public vector<V> {
#ifdef FFT_POLY_CONSTRUCT // ^
  inline FFTPoly(int size, V v) : vector<V>(size, v) {}
#endif

#ifdef FFT_POLY_ASSIGN_VECTOR // ^
  template<typename OV>
  inline void operator=(const vector<OV>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef FFT_POLY_MUL_INLINE // ^
  inline void operator*=(const FFTPoly& o) {
    // FFT_POLY_MUL_INLINE => FFT_MUL_UTILS_MUL_INLINE_REAL
    FFTMulUtils<FFT_T>::instance().mulInlineReal(*this, o, false);
  }
#endif

#ifdef FFT_POLY_MUL_INLINE_CYCLIC // ^
  inline void mulInlineCyclic(const FFTPoly& o) {
    // FFT_POLY_MUL_INLINE_CYCLIC => FFT_MUL_UTILS_MUL_INLINE_REAL
    FFTMulUtils<FFT_T>::instance().mulInlineReal(*this, o, true);
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const FFTPoly& vs) {
    o << tostring(static_cast<vector<V>>(vs));
    return o;
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename V>
inline string totype(const math::FFTPoly<V>& v) {
  return "FFTPoly<" + totype(V()) + ">";
}
#endif
