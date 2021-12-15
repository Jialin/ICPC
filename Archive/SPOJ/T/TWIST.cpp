// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_TREAP_INSERT_RIGHTMOST
#define BASE_LAZY_TREAP_RESERVE_NODES
#define BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH
#include "ds/treap/base_lazy_treap_macros.h"

#include "ds/treap/lazy_treap_reverse.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int n;
ds::LazyTreapReverse treap;
bool first;

inline void dfs(int idx) {
  if (idx < 0) {
    return;
  }
  auto& node = treap._nodes[idx];
  treap._pushAndClearUpdate(node);
  dfs(node._lIdx);
  if (!first) {
    io::writeChar(' ');
  } else {
    first = false;
  }
  io::writeInt(node._key + 1);
  dfs(node._rIdx);
}

int main() {
  int q;
  io::readInt(n);
  io::readInt(q);
  treap.reserveNodes(n);
  FOR(i, 0, n) {
    treap.insertRightmost(i, nullptr);
  }
  FOR(_, 0, q) {
    int x, y;
    io::readInt(x);
    io::readInt(y);
    if (x == y) {
      continue;
    }
    treap.updateRangeByKth(x - 1, y, true);
  }
  first = true;
  dfs(treap._roots[0]);
  io::writeChar('\n');
  return 0;
}
