#pragma once

#include "ds/sparse_table/base_sparse_table.h"

namespace ds {

template<typename V>
struct MaxSparseTable : BaseSparseTable<V> {
  inline void combine(const V& leftValue, const V& rightValue, V& res) const override {
    res = max(leftValue, rightValue);
  }
};

} // namespace ds
