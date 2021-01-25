// !macro_gen
// ALL FFT_POLY_MOD_INT_ALL
#pragma once

#ifdef _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
// _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS => INCLUDE math/fft/fft_mul_mod_utils_macros.h
#include "math/fft/fft_mul_mod_utils_macros.h"
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE
// FFT_POLY_MOD_INT_ONLINE_INLINE => INCLUDE math/fft/fft_online_mod_utils_macros.h
#include "math/fft/fft_online_mod_utils_macros.h"
#endif

#include "math/mod/mod_int_macros.h" // INCLUDE
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/mod/mod_int.h"

#ifdef _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
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

#ifdef FFT_POLY_MOD_INT_SUB // ^
  inline FFTPolyModInt operator-(const FFTPolyModInt& o) const {
    FFTPolyModInt res(max(this->size(), o.size()));
    FORSIZE(i, *this) {
      res[i] += (*this)[i];
    }
    FORSIZE(i, o) {
      res[i] -= o[i];
    }
    return res;
  }
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE // ^
  inline void operator*=(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_MUL_INLINE => _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
    // FFT_POLY_MOD_INT_MUL_INLINE => FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
    FFTMulModUtils<FFT_T>::instance().mulInlineModInt(*this, o, false);
  }
#endif

#ifdef FFT_POLY_MOD_INT_SHRINK // ^
  inline void shrink() {
    for (; this->size() > 1 && !this->back()._v; this->pop_back()) {}
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

#ifdef FFT_POLY_MOD_INT_INV_INLINE // ^
  inline void invInline() {
    static FFTPolyModInt res;
    int n = this->size();
    res.resize(n);
    FOR(i, 0, n) {
      res[i] = (*this)[i];
    }
    res._inv(*this, n);
  }

  inline void _inv(FFTPolyModInt& res, int n) {
    if (n == 1) {
      DEBUG_GT((*this)[0]._v, 0);
      res.resize(1);
      // FFT_POLY_MOD_INT_INV_INLINE => MOD_INT_INV
      res[0] = (*this)[0].inv();
      return;
    }
    int nHalf = (n + 1) >> 1;
    _inv(res, nHalf);
    static FFTPolyModInt tmp;
    tmp.resize(n);
    FOR(i, 0, n) {
      tmp[i] = (*this)[i];
    }
    // FFT_POLY_MOD_INT_INV_INLINE => _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
    // FFT_POLY_MOD_INT_INV_INLINE => FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
    auto& fft = FFTMulModUtils<FFT_T>::instance();
    fft.mulInlineModInt(tmp, res, false);
    tmp.resize(n);
    fft.mulInlineModInt(tmp, res, false);
    FOR(i, 0, n) {
      if (i < res.size()) {
        // FFT_POLY_MOD_INT_INV_INLINE => MOD_INT_MUL_INLINE
        res[i] *= 2;
      } else {
        res.emplace_back(0);
      }
      // FFT_POLY_MOD_INT_INV_INLINE => MOD_INT_SUB_INLINE
      res[i] -= tmp[i];
    }
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
