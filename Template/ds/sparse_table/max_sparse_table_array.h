#pragma once

#include "ds/sparse_table/base_sparse_table_array.h"

namespace ds {

template<typename V, int MAXBIT, int MAXN>
struct MaxSparseTableArray final : BaseSparseTableArray<V, MAXBIT, MAXN> {
  inline void combine(const V& lv, const V& rv, V& res) const override {
    res = max(lv, rv);
  }
};

} // namespace ds
