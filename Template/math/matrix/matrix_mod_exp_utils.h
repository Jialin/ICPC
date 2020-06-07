#pragma once

#include <vector>

#include "math/matrix/matrix.h"
#include "math/matrix/matrix_fix_inline.h"
#include "math/matrix/matrix_mul_inline.h"
#include "math/mod/slight_fix.h"

using namespace std;

namespace math {

template<typename V = int, typename V_SQR = long long>
class MatrixModExpUtils {
public:
  inline MatrixModExpUtils() {}

  inline MatrixModExpUtils(
      const Matrix<V>& base,
      const V& mod = 1000000007,
      const int& capacity = -1) {
    init(base, mod, capacity);
  }

  inline void init(
      const Matrix<V>& base,
      const V& mod = 1000000007,
      const int& capacity = -1) {
    assert(base.n() == base.m());
    n_ = base.n();
    mod_ = mod;
    pows_.clear();
    if (capacity > 0) {
      pows_.reserve(capacity);
    }
    pows_.emplace_back(base);
    matrixFixModInline<V>(pows_.back(), mod_);
  }

  template<typename EXP = int32_t>
  inline void exp(Matrix<V>& res, EXP e) {
    assert(e >= 0);
    res.init(n_, n_);
    for (int i = 0; i < n_; ++i) {
      res.at(i, i) = slightFixMod(1, mod_);
    }
    for (int i = 0; e > 0; e >>= 1, ++i) {
      if (!(e & 1)) {
        continue;
      }
      while (i >= static_cast<int>(pows_.size())) {
        Matrix<V> subRes;
        matrixMulModInline<V, V_SQR>(subRes, pows_.back(), pows_.back(), mod_);
        pows_.emplace_back(std::move(subRes));
      }
      matrixMulModInline<V, V_SQR>(tmpMat_, res, pows_[i], mod_);
      swap(res, tmpMat_);
    }
  }

private:
  int n_;
  V mod_;
  vector<Matrix<V>> pows_;
  Matrix<V> tmpMat_;
};

} // namespace math
