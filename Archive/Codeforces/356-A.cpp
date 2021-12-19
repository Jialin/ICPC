// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/disjoint_set/disjoint_set_max.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  ds::DisjointSetMax<int> dset;
  vector<int> idxs(n);
  FOR(i, 0, n) {
    idxs[i] = i;
  }
  dset.init(move(idxs));
  vector<int> results(n, -1);
  FOR(_, 0, m) {
    int lower, upper, v;
    io::readInt(lower);
    io::readInt(upper);
    io::readInt(v);
    --lower;
    --v;

    for (int idx = lower; idx < v;) {
      if (results[idx] < 0) {
        results[idx] = v;
      }
      int nxtIdx = dset.calcSetValue(idx) + 1;
      if (nxtIdx < v) {
        dset.unionSet(idx, nxtIdx);
      }
      idx = nxtIdx;
    }

    for (int idx = v + 1; idx < upper;) {
      if (results[idx] < 0) {
        results[idx] = v;
      }
      int nxtIdx = dset.calcSetValue(idx) + 1;
      if (nxtIdx < upper) {
        dset.unionSet(idx, nxtIdx);
      }
      idx = nxtIdx;
    }
  }
  FOR(i, 0, n) {
    io::writeInt(results[i] + 1, i + 1 == n ? '\n' : ' ');
  }
  return 0;
}
