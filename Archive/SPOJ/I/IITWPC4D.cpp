// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_INIT_ORDERED_ITEMS
#define BASE_TREAP_POP_KTH
#define BASE_TREAP_RESERVE_NODES
#define TREAP_SET_INSERT
#include "ds/treap/base_treap_macros.h"
#include "ds/treap/treap_set_macros.h"

#include "ds/treap/treap_set.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

ds::TreapSet<int> treap;
vector<int> as;
vector<pair<int, nullptr_t>> inits;

int main() {
  treap.reserveNodes(MAXN);
  as.reserve(MAXN);
  inits.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    as.resize(n);
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      io::readInt(as[i]);
      as[i] = i - as[i];
      if (valid && as[i] < 0) {
        valid = false;
      }
    }
    io::writeCharArray("Test : ");
    io::writeInt(taskIdx);
    io::writeChar('\n');
    if (!valid) {
      io::writeChar('-');
      io::writeChar('1');
      io::writeChar('\n');
      continue;
    }
    inits.clear();
    for (int i = (0); i < (n); ++i) {
      inits.emplace_back(i + 1, nullptr);
    }
    treap.clear();
    treap.initOrderedItems(inits);
    for (int i = n - 1; i >= 0; --i) {
      const auto* p = treap.popKth(as[i]);
      as[i] = p->_key;
    }
    io::writeInt(as[0]);
    for (int i = (1); i < (n); ++i) {
      io::writeChar(' ');
      io::writeInt(as[i]);
    }
    io::writeChar('\n');
  }
  return 0;
}
