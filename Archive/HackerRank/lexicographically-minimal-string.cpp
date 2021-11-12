// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_UNION_SET
#include "ds/disjoint_set/disjoint_set_size_macros.h"

#include "ds/disjoint_set/disjoint_set_size.h"
#include "io/read_char_array.h"
#include "io/write_char.h"

// Last include
#include "debug/debug.h"

const int MAXL = 100000 + 1;

char sa[MAXL], sb[MAXL], sc[MAXL];
char minC[32];

int main() {
  int n = io::readCharArray(sa);
  io::readCharArray(sb);
  int m = io::readCharArray(sc);
  ds::DisjointSetSize dset;
  dset.init(26);
  FOR(i, 0, 26) {
    minC[i] = 'a' + i;
  }
  FOR(i, 0, n) {
    int ca = sa[i] - 'a';
    int cb = sb[i] - 'a';
    int c = min(minC[dset.findSet(ca)], minC[dset.findSet(cb)]);
    dset.unionSet(ca, cb);
    minC[dset.findSet(ca)] = c;
  }
  FOR(i, 0, m) {
    io::writeChar(minC[dset.findSet(sc[i] - 'a')]);
  }
  io::writeChar('\n');
}
