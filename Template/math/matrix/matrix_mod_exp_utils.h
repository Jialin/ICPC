#pragma once

#include <vector>

#include "debug/debug.h"
#include "math/matrix/matrix_fix_inline.h"
#include "math/matrix/matrix_mul_inline.h"
#include "math/mod/slight_fix.h"

using namespace std;

namespace math {

template<typename MATRIX, typename V = int, typename V_SQR = int64_t>
struct MatrixModExpUtils {
  inline MatrixModExpUtils() {}

  inline MatrixModExpUtils(
      const MATRIX& base, const V& mod, int capacity = -1) {
    init(base, mod, capacity);
  }

  inline void init(const MATRIX& base, const V& mod, int capacity = -1) {
    DEBUG_EQ(base._n, base._m);
    _n = base._n;
    _mod = mod;
    _pows.clear();
    if (capacity > 0) {
      _pows.reserve(capacity);
    }
    _pows.emplace_back(base);
    matrixFixModInline<MATRIX, V>(_pows.back(), _mod);
  }

  template<typename EXP = int32_t>
  inline void calc(MATRIX& res, EXP e) {
    DEBUG_TRUE(e >= 0, "e(%d) should be non-negative.", e);
    res.init(_n, _n);
    for (int i = 0; i < _n; ++i) {
      res._vs[i][i] = slightFixMod<V>(1, _mod);
    }
    for (int i = 0; e > 0; e >>= 1, ++i) {
      if (!(e & 1)) {
        continue;
      }
      while (i >= static_cast<int>(_pows.size())) {
        MATRIX subRes;
        matrixMulModInline<MATRIX, V, V_SQR>(
            subRes, _pows.back(), _pows.back(), _mod);
        _pows.emplace_back(move(subRes));
      }
      matrixMulModInline<MATRIX, V, V_SQR>(_tmpMat, res, _pows[i], _mod);
      swap(res, _tmpMat);
    }
  }

  int _n;
  V _mod;
  vector<MATRIX> _pows;
  MATRIX _tmpMat;
};

} // namespace math
