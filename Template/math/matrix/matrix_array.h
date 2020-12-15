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
    DEBUG_GT(n, 0);
    DEBUG_LE(n, N);
    DEBUG_GT(m, 0);
    DEBUG_LE(m, M);
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
