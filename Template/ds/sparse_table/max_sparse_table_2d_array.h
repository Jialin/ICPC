#pragma once

#include "ds/sparse_table/base_sparse_table_2d_array.h"

namespace ds {

template<typename V, int MAXNBIT, int MAXMBIT, int MAXN, int MAXM>
struct MaxSparseTable2DArray final : BaseSparseTable2DArray<V, MAXNBIT, MAXMBIT, MAXN, MAXM> {
  inline void combineLeftRight(const V& leftValue, const V& rightValue, V& res) const override {
    res = max(leftValue, rightValue);
  }

  inline void combineUpperLower(const V& upperValue, const V& lowerValue, V& res) const override {
    res = max(upperValue, lowerValue);
  }
};

} // namespace ds
