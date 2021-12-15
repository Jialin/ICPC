#pragma once

#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/base_fenwick_2d_array.h"

namespace ds {

template<typename V, int MAXN, int MAXM>
struct Fenwick2DArrayMax : BaseFenwick2DArray<V, MAXN, MAXM> {
  inline void _initV(V& v) override {
    v = numeric_limits<V>::min();
  }

  inline void _addV(V& v, const V& deltaV) override {
    v = max(v, deltaV);
  }
};

} // namespace ds
