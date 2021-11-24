// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_CALC_SUFFIX
#define BASE_TREAP_INIT_ITEMS
#define BASE_TREAP_RESERVE_NODES
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_multiset.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int threshold;
vector<int> as;
vector<int64_t> updates;
vector<pair<int64_t, int>> updateCnts;
ds::TreapMultiset<int64_t> treap;

inline int64_t calc(int lower, int upper) {
  if (lower >= upper) {
    return 0;
  }
  if (lower + 1 == upper) {
    return as[lower] >= threshold;
  }
  int medium = (lower + upper) >> 1;
  auto res = calc(lower, medium) + calc(medium, upper);
  treap.clear();
  updates.clear();
  int64_t x = 0;
  FOR(i, medium, upper) {
    x += as[i];
    x -= threshold;
    updates.emplace_back(x);
  }
  SORT(updates);
  updateCnts.clear();
  for (auto u : updates) {
    if (updateCnts.empty() || updateCnts.back().first != u) {
      updateCnts.emplace_back(u, 1);
    } else {
      ++updateCnts.back().second;
    }
  }
  treap.initItems(updateCnts);
  x = 0;
  for (int i = medium - 1; i >= lower; --i) {
    x -= as[i];
    x += threshold;
    res += treap.calcSuffix(x);
  }
  return res;
}

int main() {
  int n;
  io::readInt(n);
  io::readInt(threshold);
  treap.reserveNodes(n);
  updates.reserve(n);
  updateCnts.reserve(n);
  as.resize(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
  }
  io::writeInt(calc(0, n));
  io::writeChar('\n');
  return 0;
}
