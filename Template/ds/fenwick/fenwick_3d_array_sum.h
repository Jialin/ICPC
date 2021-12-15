#pragma once

#include "ds/fenwick/base_fenwick_3d_array_macros.h"

#include "ds/fenwick/base_fenwick_3d_array.h"

namespace ds {

template<typename V, int MAXN, int MAXM, int MAXL>
struct Fenwick3DArraySum : BaseFenwick3DArray<V, MAXN, MAXM, MAXL> {
  inline void _initV(V& v) override {
    v = 0;
  }

  inline void _addV(V& v, const V& deltaV) override {
    v += deltaV;
  }

#ifdef BASE_FENWICK_3D_ARRAY_CALC_RANGE // ^
  inline void _subV(V& v, const V& deltaV) const override {
    v -= deltaV;
  }
#endif
};

} // namespace ds
