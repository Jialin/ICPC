// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_IS_IN_SAME_SET
#include "ds/disjoint_set/disjoint_set_size_macros.h"

#include "ds/disjoint_set/disjoint_set_size.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  ds::DisjointSetSize dset;
  dset.init(n);
  vector<pair<int, int>> edgesToRemove;
  edgesToRemove.reserve(n - 1);
  FOR(_, 1, n) {
    int u, v;
    io::readInt(u);
    io::readInt(v);
    --u;
    --v;
    if (!dset.unionSet(u, v)) {
      edgesToRemove.emplace_back(u, v);
    }
  }
  io::writeInt(SIZE(edgesToRemove));
  io::writeChar('\n');
  int pnt = 0;
  FOR(i, 1, n) {
    if (!dset.isInSameSet(i - 1, i)) {
      dset.unionSet(i - 1, i);
      io::writeInt(edgesToRemove[pnt].first + 1);
      io::writeChar(' ');
      io::writeInt(edgesToRemove[pnt].second + 1);
      io::writeChar(' ');
      io::writeInt(i);
      io::writeChar(' ');
      io::writeInt(i + 1);
      io::writeChar('\n');
      ++pnt;
    }
  }
}
