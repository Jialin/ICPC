#pragma once

#include "math/mod/fix_inline.h"

namespace math {

template<typename MATRIX, typename V = int>
inline void matrixFixModInline(MATRIX& mat, const V& mod) {
  for (int i = mat._n - 1; i >= 0; --i) {
    for (int j = mat._m - 1; j >= 0; --j) {
      fixModInline(mat._vs[i][j], mod);
    }
  }
}

} // namespace math
