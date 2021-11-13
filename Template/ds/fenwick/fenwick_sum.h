#pragma once

#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/base_fenwick.h"

namespace ds {

template<typename V>
struct FenwickSum : BaseFenwick<V> {
  inline void initV(V& v) override {
    v = 0;
  }

  inline void updateV(V& v, const V& deltaV) override {
    v += deltaV;
  }

#ifdef BASE_FENWICK_CALC_RANGE // ^
  inline V subV(const V& upperV, const V& lowerV) const override {
    return upperV - lowerV;
  }
#endif
};

} // namespace ds
