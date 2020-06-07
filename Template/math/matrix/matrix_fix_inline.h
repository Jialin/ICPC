#pragma once

#include "math/matrix/matrix.h"
#include "math/mod/fix_inline.h"

namespace math {

template<typename V = int>
inline void matrixFixModInline(Matrix<V>& mat, const V& mod) {
  for (int i = mat.n() - 1; i >= 0; --i) {
    for (int j = mat.m() - 1; j >= 0; --j) {
      fixModInline(mat.at(i, j), mod);
    }
  }
}

} // namespace math
