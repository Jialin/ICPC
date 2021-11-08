// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_CALC
#define BASE_SPARSE_TABLE_ARRAY_RESERVE
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/max_sparse_table_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  vector<int> deltaVs(n - 1);
  FOR(i, 1, n) {
    deltaVs[i - 1] = vs[i] - vs[i - 1];
  }
  ds::MaxSparseTableArray<int, 17, 100000> st;
  st.reserve(n - 1);
  st.init(move(deltaVs));
  int m;
  io::readInt(m);
  FOR(_, 0, m) {
    int v, d;
    io::readInt(v);
    io::readInt(d);
    int idx = lower_bound(ALL(vs), v + 1) - vs.begin() - 1;
    int upper = idx, res = idx;
    int lower = 0;
    while (lower < upper) {
      int medium = (lower + upper) >> 1;
      if (st.calc(medium, idx) <= d) {
        res = medium;
        upper = medium;
      } else {
        lower = medium + 1;
      }
    }
    io::writeInt(res + 1);
    io::writeChar('\n');
  }
}
