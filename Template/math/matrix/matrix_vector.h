#pragma once

#include <vector>

#include "debug/debug.h"

using namespace std;

namespace math {

template<typename V = int>
struct MatrixVector {
  inline MatrixVector() {}

  inline MatrixVector(int n, int m) {
    init(n, m);
  }

  inline void init(int n, int m) {
    DEBUG_TRUE(n > 0 && m > 0, "n(%d) and (%d) should be positive.", n, m);
    _n = n;
    _m = m;
    _vs.resize(n);
    for (auto& row : _vs) {
      row.assign(m, 0);
    }
  }

  int _n, _m;
  vector<vector<V>> _vs;
};

} // namespace math
