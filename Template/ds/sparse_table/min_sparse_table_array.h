#pragma once

#include "ds/sparse_table/base_sparse_table_array.h"

namespace ds {

template<typename V, int MAXBIT, int MAXN>
struct MinSparseTableArray : BaseSparseTableArray<V, MAXBIT, MAXN> {
  inline void combine(const V& leftValue, const V& rightValue, V& res) const override {
    res = min(leftValue, rightValue);
  }
};

} // namespace ds
