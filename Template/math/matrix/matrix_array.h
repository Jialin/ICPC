#pragma once

#include "debug/debug.h"

using namespace std;

namespace math {

template<int N, int M, typename V = int>
struct MatrixArray {
  inline MatrixArray() {}

  inline MatrixArray(int n, int m) {
    init(n, m);
  }

  inline void init(int n, int m) {
    DEBUG_TRUE(0 < n && n <= N, "n(%d) should be in range [1,%d].", n, N);
    DEBUG_TRUE(0 < m && m <= M, "m(%d) should be in range [1,%d].", m, M);
    _n = n;
    _m = m;
    for (int i = 0; i < n; ++i) {
      memset(_vs[i], 0, sizeof(V) * m);
    }
  }

  int _n, _m;
  V _vs[N][M];
};

} // namespace math
