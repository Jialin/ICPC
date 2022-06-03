// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/lazy_compact_segment_tree_update_set_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/bit/next_pow2_32.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  ds::LazyCompactSegmentTreeUpdateSetSum<int64_t, int> st;
  st.init(move(vs));
  FOR(_, 0, q) {
    int op, lower, upper;
    io::readInt(op);
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    if (op == 1) {
      int delta;
      io::readInt(delta);
      st.changeRange(lower, upper, delta);
    } else if (op == 2) {
      int delta;
      io::readInt(delta);
      st.setRange(lower, upper, delta);
    } else {
      io::writeInt(st.calcRange(lower, upper), '\n');
    }
  }
  return 0;
}
