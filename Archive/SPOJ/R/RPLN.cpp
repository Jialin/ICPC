// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_CALC
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/min_sparse_table_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;
const int MAXBIT = 17;

int main() {
  ds::MinSparseTableArray<int, MAXBIT, MAXN> st;
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n, q;
    io::readInt(n);
    io::readInt(q);
    vector<int> vs(n);
    FOR(i, 0, n) {
      io::readInt(vs[i]);
    }
    st.init(move(vs));
    io::writeCharArray("Scenario #");
    io::writeInt(taskIdx);
    io::writeChar(':');
    io::writeChar('\n');
    FOR(_, 0, q) {
      int x, y;
      io::readInt(x);
      io::readInt(y);
      if (x > y) {
        swap(x, y);
      }
      io::writeInt(st.calc(x - 1, y));
      io::writeChar('\n');
    }
  }
  return 0;
}
