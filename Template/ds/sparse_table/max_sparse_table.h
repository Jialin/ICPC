#pragma once

#include "ds/sparse_table/base_sparse_table.h"

namespace ds {

template<typename V>
struct MaxSparseTable final : BaseSparseTable<V> {
  inline void combine(const V& lv, const V& rv, V& res) const override {
    res = max(lv, rv);
  }
};

} // namespace ds
