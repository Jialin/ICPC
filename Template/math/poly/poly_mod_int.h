#pragma once

#include "math/poly/poly_mod_int_macros.h"

#ifdef _POLY_MOD_INT_NTT_UTILS_FIX
#include "math/fft/ntt_utils_fix.h"
#endif

#include "math/mod/mod_int.h"

namespace math {

template<typename V, typename V_SQR, const V PRIME>
struct PolyModInt {
  using _ModInt = ModInt<V, V_SQR, PRIME>;

#ifdef POLY_MOD_INT_CONSTRUCT
  inline PolyModInt(int size = 0, V v = 0) {
    _vs.assign(size, v);
  }
#endif

#ifdef POLY_MOD_INT_ACCESS
  inline _ModInt& operator[](int idx) {
    return _vs[idx];
  }
#endif

#ifdef POLY_MOD_INT_RESIZE
  inline void resize(int size) {
    _vs.resize(size);
  }
#endif

#ifdef POLY_MOD_INT_RESERVE
  inline void reserve(int size) {
    _vs.reserve(size);
  }
#endif

#ifdef POLY_MOD_INT_SIZE
  inline size_t size() const {
    return _vs.size();
  }
#endif

#ifdef POLY_MOD_INT_MUL_INLINE_MODIFY
  template<V ROOT>
  inline void mulInlineModify(
      PolyModInt& o, bool cyclic, NTTUtilsFix<V, V_SQR, PRIME, ROOT>& ntt) {
    ntt.mulInlineModify(_vs, o._vs, cyclic);
  }
#endif

  vector<_ModInt> _vs;
};

} // namespace math
