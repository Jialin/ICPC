#pragma once

#include "ds/sparse_table/base_sparse_table_2d.h"

namespace ds {

template<typename V>
struct MaxSparseTable2D final : BaseSparseTable2D<V> {
  inline void combineLeftRight(const V& leftValue, const V& rightValue, V& res) const override {
    res = max(leftValue, rightValue);
  }

  inline void combineUpperLower(const V& upperValue, const V& lowerValue, V& res) const override {
    res = max(upperValue, lowerValue);
  }
};

} // namespace ds
