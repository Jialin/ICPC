// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_GROUPS_RESERVE
#include "ds/disjoint_set/disjoint_set_size_groups_macros.h"

#include "ds/disjoint_set/disjoint_set_size_groups.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 50000;

ds::DisjointSetSizeGroups dset;

int main() {
  dset.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, q;
    io::readInt(n);
    io::readInt(q);
    dset.init(n, 3);
    int res = 0;
    FOR(_, 0, q) {
      int op, x, y;
      io::readInt(op);
      io::readInt(x);
      io::readInt(y);
      --x;
      --y;
      if (x < 0 || x >= n || y < 0 || y >= n) {
        ++res;
        continue;
      }
      bool valid;
      dset.unionSet(x, y, op - 1, valid);
      if (!valid) {
        ++res;
      }
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
