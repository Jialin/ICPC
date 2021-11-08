// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_CALC
#define BASE_SPARSE_TABLE_ARRAY_RESERVE
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/base_sparse_table_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

vector<int> as;

template<int MAXBIT, int MAXN>
struct MaxIndexSparseTableArray final : ds::BaseSparseTableArray<int, MAXBIT, MAXN> {
  inline void combine(const int& leftValue, const int& rightValue, int& res) const override {
    res = as[leftValue] > as[rightValue] ? leftValue : rightValue;
  }
};

MaxIndexSparseTableArray<17, 100000> st;

int main() {
  int n;
  io::readInt(n);
  as.resize(n);
  as[n - 1] = n - 1;
  FOR(i, 0, n - 1) {
    io::readInt(as[i]);
    --as[i];
  }
  vector<int> idxs(n);
  FOR(i, 0, n) {
    idxs[i] = i;
  }
  st.reserve(n);
  st.init(move(idxs));
  vector<int> cnts(n, 1);
  int64_t res = 0;
  FOR(i, 0, n - 1) {
    int idx = st.calc(i + 1, as[i] + 1);
    res += (n - 1LL - i - as[i] + idx) * cnts[i];
    cnts[idx] += cnts[i];
  }
  io::writeInt(res);
  io::writeChar('\n');
}
