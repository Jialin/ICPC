#pragma once

#include "ds/disjoint_set/base_disjoint_set_value.h"

namespace ds {

template<typename V>
struct DisjointSetMinMax : BaseDisjointSetValue<pair<V, V>> {
  void combine(const pair<V, V>& fromV, pair<V, V>& toV) const override {
    toV.first = min(toV.first, fromV.first);
    toV.second = max(toV.second, fromV.second);
  }
};

} // namespace ds
