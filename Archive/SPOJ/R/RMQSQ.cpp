// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_RESERVE
#define BASE_SPARSE_TABLE_ARRAY_CALC
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/min_sparse_table_array.h"
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
  ds::MinSparseTableArray<int, 17, 100000> st;
  st.reserve(n);
  st.init(move(vs));
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    io::writeInt(st.calc(l, r + 1));
    io::writeChar('\n');
  }
}
