// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_FOREST_CALC_PREFIX
#define BASE_TREAP_FOREST_ERASE
#define BASE_TREAP_FOREST_INIT_ORDERED_ITEMS
#define BASE_TREAP_FOREST_RESERVE_ROOTS
#define BASE_TREAP_RESERVE_NODES
#define TREAP_FOREST_SET_INSERT
#include "ds/treap/base_treap_forest_macros.h"
#include "ds/treap/treap_forest_set_macros.h"

#include "ds/treap/treap_forest_set.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000;
const int MAXQ = MAXN;
const int MAXNQ = MAXN + MAXQ;

int as[MAXN], qIdx[MAXQ], qA[MAXQ], cnts[MAXNQ];
vector<pair<int, nullptr_t>> idxs[MAXNQ];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> dis;
  dis.reserve(n + q);
  FOR(i, 0, n) {
    io::readInt(as[i]);
    dis.push_back(as[i]);
  }
  FOR(i, 0, q) {
    io::readInt(qIdx[i]);
    io::readInt(qA[i]);
    dis.push_back(qA[i]);
  }
  SORTUNIQUE(dis);
  ds::TreapForestSet<int> forest;
  forest.reserveNodes(n + q);
  int disCnt = SIZE(dis);
  forest.reserveRoots(disCnt);
  forest.init(disCnt);
  FOR(i, 0, n) {
    int a = as[i];
    a = INDEX(dis, a);
    ++cnts[a];
    as[i] = a;
  }
  FOR(i, 0, n) {
    int a = as[i];
    auto& idxsA = idxs[a];
    if (idxsA.empty()) {
      idxsA.reserve(cnts[a]);
    }
    idxsA.emplace_back(i, nullptr);
    if (idxsA.size() == cnts[a]) {
      forest.initOrderedItems(idxsA, a);
    }
  }
  FOR(i, 0, q) {
    int idx = qIdx[i];
    int a = INDEX(dis, qA[i]);
    io::writeInt(forest.calcPrefix(idx, a));
    io::writeChar('\n');
    if (as[idx] == a) {
      continue;
    }
    forest.erase(idx, as[idx]);
    forest.insert(idx, a);
    as[idx] = a;
  }
}
