// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_CALC_PREFIX
#define BASE_TREAP_RESERVE_NODES
#define BASE_TREAP_UPDATE
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  ds::TreapSum<int, int64_t> treap;
  treap.reserveNodes(n);
  int64_t l = 0;
  FOR(_, 0, n) {
    int64_t a, v;
    io::readInt(a);
    io::readInt(v);
    a ^= l;
    v ^= l;
    treap.update(a, v);
    l = treap.calcPrefix(a + 1);
    io::writeInt(a);
    io::writeChar(' ');
    io::writeInt(l);
    io::writeChar('\n');
  }
  DEBUGV(treap);
  return 0;
}
