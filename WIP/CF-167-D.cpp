// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_COMPACT_SEGMENT_TREE_INIT
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000009;

vector<pair<int, int>> positions;

struct CompactSegmentTreeMaxIndex : ds::BaseCompactSegmentTree<int, int, nullptr_t> {
  using V = int;
  using InitV = int;
  using Update = nullptr_t;
  using Node = typename CompactSegmentTreeMaxIndex::Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = -1;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    if (res < 0 || positions[res].second < positions[node.v].second) {
      res = node.v;
    }
  }
#endif

  inline void _applyUpdate(const Update& update, Node& node) override {
    assert(false);
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = positions[lNode.v].second > positions[rNode.v].second ? lNode.v : rNode.v;
  }
};

const int MAXN = 100000;
const int MAXM = MAXN << 1;

CompactSegmentTreeMaxIndex st;

int pnt;
int results[MAXM], unused[MAXM];
int leftIdxs[MAXM], rightIdxs[MAXM], mediums[MAXM];

inline int getResult(int idx) {
  return idx >= 0 ? results[idx] : 0;
}

inline int getUnused(int idx) {
  return idx >= 0 ? unused[idx] : -1;
}

inline void merge(int lIdx, int rIdx, int idx) {
  unused[idx] = getResult(lIdx) + getResult(rIdx);
  results[idx] = max(
      max(getResult(lIdx) + getUnused(rIdx), getUnused(lIdx) + getResult(rIdx)) + 1, unused[idx]);
}

inline int init(int lower, int upper) {
  if (lower >= upper) {
    return -1;
  }
  int medium = st.calcRange(lower, upper);
  int idx = pnt++;
  mediums[idx] = medium;
  leftIdxs[idx] = init(lower, medium);
  rightIdxs[idx] = init(medium + 1, upper);
  merge(leftIdxs[idx], rightIdxs[idx], idx);
  return idx;
}

int L, R;

inline pair<int, int> calc(int idx, int lower, int upper) {
  if (idx < 0 || R <= positions[lower].first || positions[upper - 1].first < L) {
    return {0, -1};
  }
  if (L <= positions[lower].first && positions[upper - 1].first < R) {
    return {results[idx], unused[idx]};
  }
  int mediumX = positions[mediums[idx]].first;
  if (R <= mediumX) {
    return calc(leftIdxs[idx], lower, mediums[idx]);
  } else if (mediumX < L) {
    return calc(rightIdxs[idx], mediums[idx] + 1, upper);
  }
  auto lv = calc(leftIdxs[idx], lower, mediums[idx]);
  auto rv = calc(rightIdxs[idx], mediums[idx] + 1, upper);
  return {
      max(max(lv.first + rv.second, lv.second + rv.first) + 1, lv.first + rv.first),
      lv.first + rv.first};
}

int main() {
  int n, k;
  io::readInt(n);
  io::readInt(k);
  positions.reserve(n);
  int lastX, lastY;
  FOR(i, 0, k) {
    io::readInt(lastX);
    io::readInt(lastY);
    positions.emplace_back(lastX, lastY);
  }
  int a, b, c, d;
  io::readInt(a);
  io::readInt(b);
  io::readInt(c);
  io::readInt(d);
  FOR(i, k, n) {
    int x = (a * (lastX + 0LL) + b) % MOD;
    int y = (c * (lastY + 0LL) + d) % MOD;
    positions.emplace_back(x, y);
    lastX = x;
    lastY = y;
  }
  sort(ALL(positions), [](const auto& x, const auto& y) {
    return x.first < y.first;
  });
  vector<int> idxs(n);
  FOR(i, 0, n) {
    idxs[i] = i;
  }
  st.init(move(idxs));
  pnt = 0;
  init(0, n);
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    io::readInt(L);
    io::readInt(R);
    ++R;
    io::writeInt(calc(0, 0, n).first);
    io::writeChar('\n');
  }
  return 0;
}
