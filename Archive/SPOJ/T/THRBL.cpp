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
  int n, m;
  io::readInt(n);
  io::readInt(m);
  vector<int> hs(n);
  FOR(i, 0, n) {
    io::readInt(hs[i]);
  }
  vector<int> hs2 = hs;
  ds::MaxSparseTableArray<int, 16, 50000> st;
  st.reserve(n);
  st.init(move(hs2));
  int res = 0;
  FOR(i, 0, m) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    if (l == r) {
      ++res;
      continue;
    }
    int h = hs[l - 1];
    if (l > r) {
      swap(l, r);
    }
    if (h == st.calc(l - 1, r - 1)) {
      ++res;
    }
  }
  io::writeInt(res);
  io::writeChar('\n');
}
