#include <vector>
using namespace std;

#include "ds/sparse_table/base_sparse_table_array.h"

vector<int> as;

template<int MAXBIT, int MAXN>
struct MaxIndexSparseTableArray final : ds::BaseSparseTableArray<int, MAXBIT, MAXN> {
  inline void combine(const int& leftValue, const int& rightValue, int& res) const override {
    res = as[leftValue] > as[rightValue] ? leftValue : rightValue;
  }
};

MaxIndexSparseTableArray<17, 100000> st;
