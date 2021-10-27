#pragma once

#include "ds/sparse_table/base_sparse_table.h"

namespace ds {

template<typename V>
struct MinSparseTable : BaseSparseTable<V> {
  inline void combine(const V& leftValue, const V& rightValue, V& res) const override {
    res = min(leftValue, rightValue);
  }
};

} // namespace ds
