// !macro_gen
// ALL FFT_POLY_MOD_INT_ALL
#pragma once

#ifndef _FFT_POLY_MOD_INT_MOD_THRESHOLD
#define _FFT_POLY_MOD_INT_MOD_THRESHOLD 16
#endif

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

template<typename FFT_T, typename MOD_INT>
struct FFTPolyModInt : public vector<MOD_INT> {
#ifdef FFT_POLY_MOD_INT_CONSTRUCT // ^

  // FFT_POLY_MOD_INT_CONSTRUCT => MOD_INT_TYPEDEF_V
  inline FFTPolyModInt(int size = 0, typename MOD_INT::V v = 0) {
    this->assign(size, v);
  }
#endif

#ifdef FFT_POLY_MOD_INT_ASSIGN // ^
  inline void operator=(const FFTPolyModInt& o) {
    this->resize(o.size());
    FORSIZE(i, o) {
      (*this)[i] = o[i];
    }
    shrink();
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
      // FFT_POLY_MOD_INT_SUB => MOD_INT_ADD_INLINE
      res[i] += (*this)[i];
    }
    FORSIZE(i, o) {
      // FFT_POLY_MOD_INT_SUB => MOD_INT_SUB_INLINE
      res[i] -= o[i];
    }
    return res;
  }
#endif

#ifdef FFT_POLY_MOD_INT_SUB_INLINE // ^
  inline void operator-=(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_SUB_INLINE => FFT_POLY_MOD_INT_EXTEND
    extend(o.size());
    for (int i = SIZE(o) - 1; i >= 0; --i) {
      // FFT_POLY_MOD_INT_SUB_INLINE => MOD_INT_SUB_INLINE
      (*this)[i] -= o[i];
    }
    // FFT_POLY_MOD_INT_SUB_INLINE => FFT_POLY_MOD_SHRINK
    shrink();
  }
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE // ^
  inline void operator*=(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_MUL_INLINE => _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
    // FFT_POLY_MOD_INT_MUL_INLINE => FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
    FFTMulModUtils<FFT_T>::instance().mulInlineModInt(*this, o, false);
  }
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE_CYCLIC // ^
  inline void mulInlineCyclic(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_MUL_INLINE_CYCLIC => _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
    // FFT_POLY_MOD_INT_MUL_INLINE_CYCLIC => FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
    FFTMulModUtils<FFT_T>::instance().mulInlineModInt(*this, o, true);
  }
#endif

#ifdef FFT_POLY_MOD_INT_DIV_INLINE // ^
  inline void operator/=(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_DIV_INLINE => FFT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < o.size()) {
      this->assign(1, 0);
      return;
    }
    static FFTPolyModInt tmpO;
    // FFT_POLY_MOD_INT_DIV_INLINE => FFT_POLY_MOD_INT_ASSIGN
    tmpO = o;
    tmpO.shrink();
    int size = this->size() - tmpO.size() + 1;
    reverse(this->begin(), this->end());
    this->resize(size);
    // FFT_POLY_MOD_INT_DIV_INLINE => FFT_POLY_MOD_INT_INV_INLINE
    reverse(tmpO.begin(), tmpO.end());
    tmpO.invInline(size);
    // FFT_POLY_MOD_INT_DIV_INLINE => FFT_POLY_MOD_INT_MUL_INLINE
    *this *= tmpO;
    this->resize(size);
    reverse(this->begin(), this->end());
    shrink();
  }
#endif

#ifdef FFT_POLY_MOD_INT_MOD_INLINE // ^
  inline void operator%=(const FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_MOD_INLINE => FFT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < o.size()) {
      return;
    }
    if (this->size() - o.size() < _FFT_POLY_MOD_INT_MOD_THRESHOLD) {
      DEBUG_GE(o.size(), 1);
      DEBUG_NE(o.back()._v, 0);
      static MOD_INT inv;
      // FFT_POLY_MOD_INT_MOD_INLINE => MOD_INT_INV
      inv = o.back().inv();
      for (int i = SIZE(*this) - 1; i >= SIZE(o) - 1; --i) {
        if (!(*this)[i]._v) {
          continue;
        }
        static MOD_INT mul;
        // FFT_POLY_MOD_INT_MOD_INLINE => MOD_INT_INIT_MUL
        mul.initMul((*this)[i], inv);
        for (int j = i - SIZE(o) + 1, k = 0; j <= i; ++j, ++k) {
          // FFT_POLY_MOD_INT_MOD_INLINE => MOD_INT_MUL
          (*this)[j] -= mul * o[k];
        }
      }
      shrink();
      return;
    }
    static FFTPolyModInt tmp;
    // FFT_POLY_MOD_INT_MOD_INLINE => FFT_POLY_MOD_INT_ASSIGN
    tmp = *this;
    // FFT_POLY_MOD_INT_MOD_INLINE => FFT_POLY_MOD_INT_DIV_INLINE
    tmp /= o;
    // FFT_POLY_MOD_INT_MOD_INLINE => _FFT_POLY_MOD_INT_MOD_SUB_INLINE_MUL
    _subInlineMul(tmp, o);
  }
#endif

#ifdef FFT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED // ^
  inline void divInlinePrecomputed(const FFTPolyModInt& invRevO) {
    // FFT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED => FFT_POLY_MOD_INT_SHRINK
    shrink();
    if (this->size() < invRevO.size()) {
      this->assign(1, 0);
      return;
    }
    // FFT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED => FFT_POLY_MOD_INT_ASSIGN
    int size = this->size() - invRevO.size() + 1;
    reverse(this->begin(), this->end());
    this->resize(size);
    static FFTPolyModInt tmpO;
    tmpO.resize(size);
    FOR(i, 0, size) {
      tmpO[i] = invRevO[i];
    }
    // FFT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED => FFT_POLY_MOD_INT_MUL_INLINE
    *this *= tmpO;
    this->resize(size);
    reverse(this->begin(), this->end());
    shrink();
  }
#endif

#ifdef FFT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED // ^
  inline void modInlinePrecomputed(const FFTPolyModInt& o, const FFTPolyModInt& invRevO) {
    if (this->size() < invRevO.size()) {
      return;
    }
    static FFTPolyModInt tmp;
    // FFT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => FFT_POLY_MOD_INT_ASSIGN
    tmp = *this;
    // FFT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => FFT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED
    tmp.divInlinePrecomputed(invRevO);
    // FFT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED => _FFT_POLY_MOD_INT_MOD_SUB_INLINE_MUL
    _subInlineMul(tmp, o);
  }
#endif

#ifdef _FFT_POLY_MOD_INT_MOD_SUB_INLINE_MUL
  inline void _subInlineMul(FFTPolyModInt& a, const FFTPolyModInt& b) {
    int aSize = a.size();
    int mask = nextPow2_32(max(a.size(), b.size())) - 1;
    int shift = (a.size() + b.size() - 1) & mask;
    // _FFT_POLY_MOD_INT_MOD_SUB_INLINE_MUL => FFT_POLY_MOD_INT_MUL_INLINE_CYCLIC
    a.mulInlineCyclic(b);
    // _FFT_POLY_MOD_INT_MOD_SUB_INLINE_MUL => FFT_POLY_MOD_INT_EXTEND
    a.extend(mask + 1);
    for (int i = 0, j = a.size() - 1 + shift; i < aSize; ++i, --j) {
      // _FFT_POLY_MOD_INT_MOD_SUB_INLINE_MUL => MOD_INT_SUB_INLINE
      a[j & mask] -= (*this)[this->size() - 1 - i];
    }
    this->resize(this->size() - aSize);
    int j = a.size() - aSize + shift - this->size();
    if (j < 0) {
      j = j % (mask + 1) + mask + 1;
    }
    j &= mask;
    for (int i = 0; i < this->size(); ++i, ++j) {
      (*this)[i] -= a[j & mask];
    }
  }
#endif

#ifdef FFT_POLY_MOD_INT_POW_MOD_INLINE // ^
  template<typename EXP>
  inline void powModInline(const FFTPolyModInt& o, EXP e) {
    // FFT_POLY_MOD_INT_POW_MOD_INLINE => FFT_POLY_MOD_INT_MOD_INLINE
    *this %= o;
    static FFTPolyModInt mul;
    // FFT_POLY_MOD_INT_POW_MOD_INLINE => FFT_POLY_MOD_INT_ASSIGN
    mul = *this;
    this->assign(1, 1);
    for (; e > 0; e >>= 1) {
      if (e & 1) {
        // FFT_POLY_MOD_INT_POW_MOD_INLINE => FFT_POLY_MOD_INT_MUL_INLINE
        *this *= mul;
        *this %= o;
      }
      if (e > 1) {
        mul *= mul;
        mul %= o;
      }
    }
  }
#endif

#ifdef FFT_POLY_MOD_INT_INIT_POW_MOD_MEMO // ^
  template<typename EXP>
  inline void initPowModMemo(
      const FFTPolyModInt& bases,
      const FFTPolyModInt& o,
      const FFTPolyModInt& invRevO,
      EXP e,
      vector<FFTPolyModInt>& memo) {
    if (memo.empty()) {
      memo.push_back(bases);
      // FFT_POLY_MOD_INT_INIT_POW_MOD_MEMO => FFT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED
      memo.back().modInlinePrecomputed(o, invRevO);
    }
    this->assign(1, 1);
    for (int i = 0; e > 0; e >>= 1, ++i) {
      if (e & 1) {
        // FFT_POLY_MOD_INT_INIT_POW_MOD_MEMO => FFT_POLY_MOD_INT_MUL_INLINE
        *this *= memo[i];
        this->modInlinePrecomputed(o, invRevO);
      }
      if (e > 1 && i >= SIZE(memo) - 1) {
        memo.push_back(memo.back());
        memo.back() *= memo.back();
        memo.back().modInlinePrecomputed(o, invRevO);
      }
    }
  }
#endif

#ifdef FFT_POLY_MOD_INT_RESULTANT_MODIFY // ^
  inline MOD_INT resultantModify(FFTPolyModInt& o) {
    // FFT_POLY_MOD_INT_RESULTANT_MODIFY => FFT_POLY_MOD_INT_SHRINK
    this->shrink();
    o.shrink();
    if (this->empty() || o.empty() || (o.size() == 1 && !o.back()._v)) {
      return 0;
    }
    if (o.size() == 1) {
      // FFT_POLY_MOD_INT_RESULTANT_MODIFY => MOD_INT_EXP
      return o.back().exp(this->size() - 1);
    }
    int degree = this->size();
    // FFT_POLY_MOD_INT_RESULTANT_MODIFY => FFT_POLY_MOD_INT_MOD_INLINE
    *this %= o;
    this->shrink();
    degree -= this->size();
    MOD_INT mul = o.back().exp(degree);
    if ((this->size() - 1) & (o.size() - 1) & 1) {
      // FFT_POLY_MOD_INT_RESULTANT_MODIFY => MOD_INT_NEGATE_INLINE
      mul.negateInline();
    }
    // FFT_POLY_MOD_INT_RESULTANT_MODIFY => MOD_INT_MUL
    return o.resultantModify(*this) * mul;
  }
#endif

#ifdef FFT_POLY_MOD_INT_INV_INLINE // ^
  inline void invInline(int size = -1) {
    static FFTPolyModInt tmpP;
    int n = size < 0 ? this->size() : size;
    tmpP.resize(n);
    FOR(i, 0, n) {
      if (i < this->size()) {
        tmpP[i] = (*this)[i];
      } else {
        tmpP[i] = 0;
      }
    }
    // FFT_POLY_MOD_INT_INV_INLINE => _FFT_POLY_MOD_INT_INV
    tmpP._inv(*this, n);
  }
#endif

#ifdef FFT_POLY_MOD_INT_INV // ^
  inline FFTPolyModInt inv(int size = -1) const {
    FFTPolyModInt res;
    // FFT_POLY_MOD_INT_INV => FFT_POLY_MOD_INT_ASSIGN
    res = *this;
    // FFT_POLY_MOD_INT_INV => FFT_POLY_MOD_INT_INV_INLINE
    res.invInline(size);
    return res;
  }
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE // ^
  inline void onlineInline(
      const FFTPolyModInt& o,
      int computedBound,
      int toComputeBound,
      const function<void(MOD_INT& f, int idx)>& transform) {
    // FFT_POLY_MOD_INT_ONLINE_INLINE => FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT
    FFTOnlineModUtils<FFT_T>::instance().onlineInlineModInt(
        *this, o, computedBound, toComputeBound, transform);
  }
#endif

// Compute k-th element in linear recurrence relations.
//   x_n = coef_0 * x_{n-d} + coef_1 * x_{n-d+1} + ... + coef_{d-1} * x_{n-1}
// Given, x_0, ... x_{d-1}, compute x_k
//
// Reference: https://discuss.codechef.com/t/rng-editorial/10068/5
#ifdef FFT_POLY_MOD_INT_RECURRENCE // ^
  template<typename K>
  inline MOD_INT recurrence(const FFTPolyModInt& xs, K k) const {
    DEBUG_GE(k, 0);
    DEBUG_EQ(this->size(), xs.size());
    int n = this->size();
    if (k < n) {
      return xs[k];
    }
    static FFTPolyModInt qs;
    qs.resize(n + 1);
    qs[0] = 1;
    for (int i = 1, j = n - 1; j >= 0; ++i, --j) {
      qs[i] = (*this)[j];
      // FFT_POLY_MOD_INT_RECURRENCE => MOD_INT_NEGATE_INLINE
      qs[i].negateInline();
    }
    static FFTPolyModInt ps;
    ps = qs;
    // FFT_POLY_MOD_INT_RECURRENCE => FFT_POLY_MOD_INT_MUL_INLINE
    ps *= xs;
    // FFT_POLY_MOD_INT_RECURRENCE => FFT_POLY_MOD_INT_TRUNCATE
    ps.truncate(n);
    for (; k > n; k >>= 1) {
      static FFTPolyModInt qsNegate;
      qsNegate = qs;
      for (int i = 1; i < qsNegate.size(); i += 2) {
        qsNegate[i].negateInline();
      }
      ps *= qsNegate;
      qs *= qsNegate;
      int idx = 0;
      for (int i = k & 1; i < ps.size(); ++idx, i += 2) {
        ps[idx] = ps[i];
      }
      ps.resize(idx);
      idx = 0;
      for (int i = 0; i < qs.size(); ++idx, i += 2) {
        qs[idx] = qs[i];
      }
      qs.resize(idx);
    }
    // FFT_POLY_MOD_INT_RECURRENCE => FFT_POLY_MOD_INT_INV_INLINE
    qs.invInline(k + 1);
    ps.truncate(k + 1);
    ps *= qs;
    if (k < ps.size()) {
      return ps[k];
    } else {
      return 0;
    }
  }
#endif

#ifdef FFT_POLY_MOD_INT_EXTEND // ^
  inline void extend(int size) {
    for (; this->size() < size; this->emplace_back(0)) {}
  }
#endif

#ifdef FFT_POLY_MOD_INT_SHRINK // ^
  inline void shrink() {
    for (; this->size() > 1 && !this->back()._v; this->pop_back()) {}
  }
#endif

#ifdef FFT_POLY_MOD_INT_TRUNCATE // ^
  inline void truncate(int size) {
    if (this->size() > size) {
      this->resize(size);
    }
  }
#endif

#ifdef _FFT_POLY_MOD_INT_INV
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
    o << tostring(static_cast<vector<MOD_INT>>(vs));
    return o;
  }
#endif
};

} // namespace math

#ifdef LOCAL
template<typename FFT_T, typename MOD_INT>
inline string totype(const math::FFTPolyModInt<FFT_T, MOD_INT>& v) {
  return "FFTPolyModInt<" + totype(FFT_T()) + "," + totype(MOD_INT::V()) + "," +
         totype(MOD_INT::V_SQR()) + "," + tostring(MOD_INT::MOD) + ">";
}
#endif
