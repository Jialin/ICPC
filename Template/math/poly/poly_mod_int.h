#pragma once

#include "math/poly/poly_mod_int_macros.h"

#ifdef _POLY_MOD_INT_NTT_UTILS_FIX
#include "math/fft/ntt_utils_fix.h"
#endif

#ifdef _POLY_MOD_INT_FFT_UTILS
#include "math/fft/fft_utils.h"
#endif

#include "debug/debug_basic.h"
#include "math/mod/mod_int.h"

namespace math {

template<typename V, typename V_SQR, const V PRIME>
struct PolyModInt : vector<ModInt<V, V_SQR, PRIME>> {
  using _ModInt = ModInt<V, V_SQR, PRIME>;

#ifdef POLY_MOD_INT_CONSTRUCT
  inline PolyModInt(int size = 0, V v = 0) {
    this->assign(size, v);
  }
#endif

#ifdef POLY_MOD_INT_ASSIGN_INT_VECTOR
  inline void operator=(const vector<V>& vs) {
    this->resize(vs.size());
    for (size_t i = 0; i < vs.size(); ++i) {
      (*this)[i] = vs[i];
    }
  }
#endif

#ifdef POLY_MOD_INT_ADD_INLINE
  inline void operator+=(PolyModInt o) {
    if (o.size() > this->size()) {
      this->reserve(o.size());
      for (size_t i = this->size(); i < o.size(); ++i) {
        this->emplace_back(0);
      }
    }
    for (size_t i = 0; i < o.size(); ++i) {
      (*this)[i] += o[i];
    }
  }
#endif

#ifdef POLY_MOD_INT_SUB
  inline PolyModInt operator-(PolyModInt o) const {
    PolyModInt res(max(this->size(), o.size()));
    for (size_t i = 0; i < this->size(); ++i) {
      res[i] += (*this)[i];
    }
    for (size_t i = 0; i < o.size(); ++i) {
      res[i] -= o[i];
    }
    return res;
  }
#endif

#ifdef POLY_MOD_INT_MUL_INT
  inline PolyModInt operator*(V scale) const {
    PolyModInt res = *this;
    res *= scale;
    return res;
  }
#endif

#ifdef POLY_MOD_INT_MUL_INLINE_INT
  inline void operator*=(V scale) {
    for (auto& x : *this) {
      x *= scale;
    }
  }
#endif

#ifdef POLY_MOD_INT_NEGATE_INLINE
  inline void negateInline() {
    for (auto& x : *this) {
      x.negateInline();
    }
  }
#endif

#ifdef POLY_MOD_INT_SHRINK
  inline void shrink() {
    for (; this->size() > 1 && !this->back()._v; this->pop_back()) {}
  }
#endif

#ifdef POLY_MOD_INT_FFT_MUL_INLINE
  template<typename T>
  inline void fftMulInline(const PolyModInt& o, FFTUtils<T>& fft) {
    fft.mulInlineModInt(*this, o);
  }
#endif

#ifdef POLY_MOD_INT_NTT_MUL_INLINE_MODIFY
  template<V ROOT>
  inline void nttMulInlineModify(
      PolyModInt& o, bool cyclic, NTTUtilsFix<V, V_SQR, PRIME, ROOT>& ntt) {
    ntt.mulInlineModify(*this, o, cyclic);
  }
#endif

#ifdef POLY_MOD_INT_NTT_NTT_INLINE
  template<V ROOT>
  inline void
  nttInline(bool invert, int pow2, NTTUtilsFix<V, V_SQR, PRIME, ROOT>& ntt) {
    ntt.ntt(*this, invert, pow2);
  }
#endif

#ifdef POLY_MOD_INT_FFT_INV
  template<typename T>
  inline PolyModInt fftInv(FFTUtils<T>& fft) {
    PolyModInt res = *this;
    res.fftInvInline(fft);
    return res;
  }
#endif

#ifdef POLY_MOD_INT_FFT_INV_INLINE
  template<typename T>
  inline void fftInvInline(FFTUtils<T>& fft) {
    int n = this->size();
    if (n == 1) {
      (*this)[0].invInline();
      return;
    }
    PolyModInt half = *this;
    half.resize((n + 1) >> 1);
    half.fftInvInline(fft);
    this->fftMulInline(half, fft);
    this->fftMulInline(half, fft);
    half *= 2;
    this->resize(n);
    this->negateInline();
    *this += half;
  }
#endif

#ifdef POLY_MOD_INT_NTT_RECURRENCE_INLINE
  // Computes f[i], computedBound<=i<toComputeBound, where
  // - f[i]=sum(f[j]*g[i-j], 0<=j<i)
  // - 0<=i<computedBound, f[i] is computed
  template<V ROOT>
  inline void nttRecurrenceInline(
      const PolyModInt& g,
      int computedBound,
      int toComputeBound,
      const function<void(_ModInt& f, int idx)>& transform,
      NTTUtilsFix<V, V_SQR, PRIME, ROOT>& ntt) {
    ntt.recurrenceInline(*this, g, computedBound, toComputeBound, transform);
  }
#endif

#ifdef POLY_MOD_INT_FFT_RECURRENCE_INLINE
  // Computes f[i], computedBound<=i<toComputeBound, where
  // - f[i]=sum(f[j]*g[i-j], 0<=j<i)
  // - 0<=i<computedBound, f[i] is computed
  template<typename T>
  inline void fftRecurrenceInline(
      const PolyModInt& g,
      int computedBound,
      int toComputeBound,
      const function<void(int& f, int idx)>& transform,
      FFTUtils<T>& fft) {
    fft.recurrenceInlineMod(*this, g, computedBound, toComputeBound, transform);
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const PolyModInt& vs) {
    o << tostring(static_cast<vector<_ModInt>>(vs));
    return o;
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename V, typename V_SQR, V PRIME>
inline string totype(const math::PolyModInt<V, V_SQR, PRIME>& v) {
  return "PolyModInt<" + totype(V()) + "," + totype(V_SQR()) + "," +
         tostring(PRIME) + ">";
}
#endif
