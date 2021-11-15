#pragma once

#include "ds/fenwick/base_fenwick.h"

namespace ds {

template<typename V>
struct FenwickMax : BaseFenwick<V> {
  inline void initV(V& v) override {
    v = numeric_limits<V>::min();
  }

  inline void updateV(V& v, const V& deltaV) override {
    if (v < deltaV) {
      v = deltaV;
    }
  }
};

} // namespace ds
