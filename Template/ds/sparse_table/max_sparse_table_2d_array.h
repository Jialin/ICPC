#pragma once

#include "ds/sparse_table/base_sparse_table_2d_array.h"

namespace ds {

template<typename V, int MAXNBIT, int MAXMBIT, int MAXN, int MAXM>
struct MaxSparseTable2DArray final : BaseSparseTable2DArray<V, MAXNBIT, MAXMBIT, MAXN, MAXM> {
  inline void combineLeftRight(const V& lv, const V& rv, V& res) const override {
    res = max(lv, rv);
  }

  inline void combineUpperLower(const V& uv, const V& lv, V& res) const override {
    res = max(uv, lv);
  }
};

} // namespace ds
