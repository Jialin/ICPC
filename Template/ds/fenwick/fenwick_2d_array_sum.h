#pragma once

#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/base_fenwick_2d_array.h"

namespace ds {

template<typename V, int MAXN, int MAXM>
struct Fenwick2DArraySum : BaseFenwick2DArray<V, MAXN, MAXM> {
  inline void initV(V& v) override {
    v = 0;
  }

  inline void updateV(V& v, const V& deltaV) override {
    v += deltaV;
  }

#ifdef BASE_FENWICK_2D_ARRAY_CALC_RANGE // ^
  inline V subV(const V& upperV, const V& lowerV) const override {
    return upperV - lowerV;
  }
#endif
};

} // namespace ds
