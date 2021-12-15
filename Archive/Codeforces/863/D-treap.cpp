// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_TREAP_CALC_KTH
#define BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH
#define BASE_LAZY_TREAP_INSERT_RIGHTMOST
#define BASE_LAZY_TREAP_RESERVE_NODES
#define BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH
#include "ds/treap/base_lazy_treap_macros.h"

#include "ds/treap/lazy_treap_reverse.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

ds::LazyTreapReverse treap;

int main() {
  int n, q, m;
  io::readInt(n);
  io::readInt(q);
  io::readInt(m);
  treap.reserveNodes(n);
  FOR(i, 0, n) {
    treap.insertRightmost(i, nullptr);
  }
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  FOR(_, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    if (op == 1) {
      treap.cyclicRotateRightByKth(x - 1, y);
    } else if (op == 2) {
      treap.updateRangeByKth(x - 1, y, true);
    }
  }
  FOR(i, 0, m) {
    int x;
    io::readInt(x);
    io::writeInt(vs[treap.calcKth(x - 1)->_key]);
    io::writeChar(i + 1 == m ? '\n' : ' ');
  }
  return 0;
}
