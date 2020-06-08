#pragma once

#include "math/matrix/matrix_mod_exp_utils.h"

namespace math {

template<typename V = int, typename V_SQR = long long>
class FibUtils {
public:
  inline FibUtils(const V& mod, int capacity = -1) {
    mod_ = mod;
    Matrix<V> base(2, 2);
    base.at(0, 1) = 1;
    base.at(1, 0) = 1;
    base.at(1, 1) = 1;
    expUtils_.init(std::move(base), mod, capacity);
  }

  template<typename EXP = int>
  inline V exp(EXP e) {
    res_.init(2, 2);
    expUtils_.template exp<EXP>(res_, e);
    return res_.at(1, 0);
  }

private:
  V mod_;
  MatrixModExpUtils<V, V_SQR> expUtils_;
  Matrix<V> res_;
};

} // namespace math
