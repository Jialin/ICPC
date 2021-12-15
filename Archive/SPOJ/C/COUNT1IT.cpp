// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_CALC_KTH_BY_RANGE
#define BASE_TREAP_CALC_PREFIX
#define BASE_TREAP_INIT_ORDERED_ITEMS
#define BASE_TREAP_RESERVE_NODES
#define TREAP_MULTISET_INSERT
#include "ds/treap/base_treap_macros.h"
#include "ds/treap/treap_multiset_macros.h"

#include "ds/treap/treap_multiset.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> as(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
  }
  SORT(as);
  vector<pair<int, int>> inits;
  inits.reserve(n);
  FOR(i, 0, n) {
    if (inits.empty() || inits.back().first != as[i]) {
      inits.emplace_back(as[i], 1);
    } else {
      ++inits.back().second;
    }
  }
  ds::TreapMultiset<int> treap;
  treap.reserveNodes(n + q);
  treap.initOrderedItems(inits);
  FOR(_, 0, q) {
    int op, x;
    io::readInt(op);
    io::readInt(x);
    if (op == 1) {
      treap.insert(x + treap.calcPrefix(x + 1));
      continue;
    }
    if (op == 2) {
      io::writeInt(treap.calcPrefix(x + 1));
    } else {
      const auto* res = treap.calcKthByRange(x - 1);
      if (!res) {
        io::writeCharArray("invalid");
      } else {
        io::writeInt(res->_key);
      }
    }
    io::writeChar('\n');
  }
}
