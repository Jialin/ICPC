#include "ds/sparse_table/base_disjoint_sparse_table.h"
#include "math/mod/mul.h"

int MOD;

template<int MAXNBIT, int MAXN>
struct ProductModDisjointSparseTable : ds::BaseDisjointSparseTable<int, MAXNBIT, MAXN> {
  inline void combine(const int& leftValue, const int& rightValue, int& res) const override {
    res = math::mulMod(leftValue, rightValue, MOD);
  }
};
