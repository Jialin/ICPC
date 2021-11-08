// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/sparse_table/max_sparse_table_2d_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

ds::MaxSparseTable2DArray<int16_t, 10, 10, 1000, 1000> st;

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  vector<vector<int16_t>> dp(n, vector<int16_t>(m));
  FOR(i, 0, n) FOR(j, 0, m) {
    io::readInt(dp[i][j]);
  }
  FOR(i, 1, n) FORIF(j, 1, m, dp[i][j]) {
    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
  }
  st.init(move(dp));
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    int x1, y1, x2, y2;
    io::readInt(x1);
    io::readInt(y1);
    io::readInt(x2);
    io::readInt(y2);
    --x1;
    --y1;
    int res = 0;
    int lower = 1;
    int upper = min(x2 - x1, y2 - y1) + 1;
    while (lower < upper) {
      int medium = (lower + upper) >> 1;
      if (st.calc(x1 + medium - 1, y1 + medium - 1, x2, y2) >= medium) {
        res = medium;
        lower = medium + 1;
      } else {
        upper = medium;
      }
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
}
