#pragma once

#include "math/matrix/matrix_array.h"
#include "math/matrix/matrix_mod_exp_utils.h"

namespace math {

// TODO: update to use Kitamasa method instead
template<typename V = int, typename V_SQR = long long>
struct FibUtils {
  inline FibUtils(const V& mod, int capacity = -1) {
    MatrixArray<2, 2, V> base;
    base.init(2, 2);
    base._vs[0][0] = 0;
    base._vs[0][1] = 1;
    base._vs[1][0] = 1;
    base._vs[1][1] = 1;
    _expUtils.init(std::move(base), mod, capacity);
  }

  template<typename EXP = int>
  inline V exp(EXP e) {
    _res.init(2, 2);
    _expUtils.template calc<EXP>(_res, e);
    return _res._vs[1][0];
  }

  MatrixModExpUtils<MatrixArray<2, 2, V>, V, V_SQR> _expUtils;
  MatrixArray<2, 2, V> _res;
};

} // namespace math
