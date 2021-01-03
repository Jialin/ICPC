#pragma once

#include "math/poly/poly_int_macros.h"

#ifdef _POLY_INT_FFT_UTILS
#include "math/fft/fft_utils.h"
#endif

namespace math {

template<typename V = int>
struct PolyInt {
#ifdef POLY_INT_CONSTRUCT
  inline PolyInt(int size = 0, V v = 0) {
    _vs.assign(size, v);
  }
#endif

#ifdef POLY_INT_ACCESS
  inline V& operator[](int idx) {
    return _vs[idx];
  }
#endif

#ifdef POLY_INT_RESIZE
  inline void resize(int size) {
    _vs.resize(size);
  }
#endif

#ifdef POLY_INT_ASSIGN
  inline void assign(int size, const V& v) {
    _vs.assign(size, v);
  }
#endif

#ifdef POLY_INT_RESERVE
  inline void reserve(int size) {
    _vs.reserve(size);
  }
#endif

#ifdef POLY_INT_SIZE
  inline size_t size() const {
    return _vs.size();
  }
#endif

#ifdef POLY_INT_MUL_INLINE
  template<typename T>
  inline void mulInline(const PolyInt& o, bool cyclic, FFTUtils<T>& fft) {
    fft.mulInlineInt(_vs, o._vs, cyclic);
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const PolyInt& v) {
    o << tostring(v._vs);
    return o;
  }
#endif

  vector<V> _vs;
};

} // namespace math

#ifdef LOCAL
template<typename V>
inline string totype(const math::PolyInt<V>& v) {
  return "PolyInt<" + totype(V()) + ">";
}
#endif
