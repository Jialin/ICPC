#pragma once

#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/base_fenwick.h"

namespace ds {

template<typename V>
struct FenwickSum : BaseFenwick<V> {
  inline void _initV(V& v) override {
    v = 0;
  }

  inline void _updateV(V& v, const V& deltaV) override {
    v += deltaV;
  }

#ifdef _BASE_FENWICK_SUB_V // ^
  inline V _subV(const V& upperV, const V& lowerV) const override {
    return upperV - lowerV;
  }
#endif
};

} // namespace ds
