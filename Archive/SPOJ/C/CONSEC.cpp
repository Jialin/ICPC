// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_RESERVE
#define DISJOINT_SET_SIZE_UNION_SET
#define DISJOINT_SET_SIZE_CALC_SET_SIZE
#include "ds/disjoint_set/disjoint_set_size_macros.h"

#include "ds/disjoint_set/disjoint_set_size.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000 + 1;
const int MAXQ = 100000;

int n;
char s[MAXN];
vector<int> ops, idxs, ress;
vector<bool> covered;
ds::DisjointSetSize dset;

void connect(int u) {
  if (u > 0 && !covered[u - 1] && s[u - 1] == s[u]) {
    dset.unionSet(u - 1, u);
  }
  if (u + 1 < n && !covered[u + 1] && s[u] == s[u + 1]) {
    dset.unionSet(u, u + 1);
  }
}

int main() {
  ops.reserve(MAXQ);
  idxs.reserve(MAXQ);
  ress.reserve(MAXQ);
  covered.reserve(MAXN);
  dset.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int q;
    n = io::readCharArray(s);
    io::readInt(q);
    ops.resize(q);
    idxs.resize(q);
    covered.resize(n);
    FOR(i, 0, q) {
      io::readInt(ops[i]);
      io::readInt(idxs[i]);
      if (ops[i] == 2) {
        covered[idxs[i]] = true;
      }
    }
    dset.init(n);
    FOR(i, 0, n) {
      if (covered[i]) {
        continue;
      }
      connect(i);
    }
    ress.clear();
    for (int i = q - 1; i >= 0; --i) {
      int j = idxs[i];
      if (ops[i] == 1) {
        ress.push_back(dset.calcSetSize(j));
      } else {
        covered[j] = false;
        connect(j);
      }
    }
    reverse(ALL(ress));
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeChar(':');
    io::writeChar('\n');
    for (int v : ress) {
      io::writeInt(v);
      io::writeChar('\n');
    }
  }
  return 0;
}
