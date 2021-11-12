// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/disjoint_set/disjoint_set_size.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int n, m;

int main() {
  io::readInt(n);
  io::readInt(m);
  vector<int> as(m), bs(m);
  FOR(i, 0, m) {
    io::readInt(as[i]);
    io::readInt(bs[i]);
    --as[i];
    --bs[i];
  }
  int q;
  io::readInt(q);
  vector<int> qIdxs(q);
  vector<bool> used(m);
  FOR(i, 0, q) {
    io::readInt(qIdxs[i]);
    used[--qIdxs[i]] = true;
  }
  ds::DisjointSetSize dset;
  dset.init(n);
  int res = n;
  FOR(i, 0, m) {
    if (!used[i]) {
      res -= dset.unionSet(as[i], bs[i]);
    }
  }
  vector<int> cnts(q);
  for (int i = q - 1; i >= 0; --i) {
    int idx = qIdxs[i];
    cnts[i] = res;
    res -= dset.unionSet(as[idx], bs[idx]);
  }
  FOR(i, 0, q) {
    io::writeInt(cnts[i]);
    io::writeChar(i + 1 == q ? '\n' : ' ');
  }
}
