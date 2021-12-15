#pragma once

#include "ds/sparse_table/base_sparse_table_2d.h"

namespace ds {

template<typename V>
struct MaxSparseTable2D final : BaseSparseTable2D<V> {
  inline void combineLeftRight(const V& lv, const V& rv, V& res) const override {
    res = max(lv, rv);
  }

  inline void combineUpperLower(const V& uv, const V& lv, V& res) const override {
    res = max(uv, lv);
  }
};

} // namespace ds
