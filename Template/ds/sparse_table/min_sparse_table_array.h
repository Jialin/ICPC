#pragma once

#include "ds/sparse_table/base_sparse_table_array.h"

namespace ds {

template<typename V, int MAXBIT, int MAXN>
struct MinSparseTableArray : BaseSparseTableArray<V, MAXBIT, MAXN> {
  inline void combine(const V& lv, const V& rv, V& res) const override {
    res = min(lv, rv);
  }
};

} // namespace ds
