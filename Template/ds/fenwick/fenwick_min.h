#pragma once

#include "ds/fenwick/base_fenwick.h"

namespace ds {

template<typename V>
struct FenwickMin : BaseFenwick<V> {
  inline void _initV(V& v) override {
    v = numeric_limits<V>::max();
  }

  inline void _updateV(V& v, const V& deltaV) override {
    if (v > deltaV) {
      v = deltaV;
    }
  }
};

} // namespace ds
