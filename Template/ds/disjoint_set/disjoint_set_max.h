#pragma once

#include "ds/disjoint_set/base_disjoint_set_value_macros.h"

#include "ds/disjoint_set/base_disjoint_set_value.h"

namespace ds {

template<typename V>
struct DisjointSetMax : BaseDisjointSetValue<V> {
  void combine(const V& fromV, V& toV) const override {
    toV = max(toV, fromV);
  }
};

} // namespace ds
