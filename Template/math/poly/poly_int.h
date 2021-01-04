#pragma once

#include "math/poly/poly_int_macros.h"

#ifdef _POLY_INT_FFT_UTILS
#include "math/fft/fft_utils.h"
#endif

namespace math {

template<typename V = int>
struct PolyInt : vector<V> {
#ifdef POLY_INT_ASSIGN_VECTOR
  inline void operator=(const vector<V>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef POLY_INT_MUL
  template<typename T>
  inline vector<Complex<T>>
  mul(const PolyInt& o, bool cyclic, FFTUtils<T>& fft) {
    return fft.mulInt(*this, o, cyclic);
  }
#endif

#ifdef POLY_INT_MUL_INLINE
  template<typename T>
  inline void mulInline(const PolyInt& o, bool cyclic, FFTUtils<T>& fft) {
    fft.mulInlineInt(*this, o, cyclic);
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename V>
inline string totype(const math::PolyInt<V>& v) {
  return "PolyInt<" + totype(V()) + ">";
}
#endif
