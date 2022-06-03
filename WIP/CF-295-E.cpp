// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_RESERVE
#define BASE_COMPACT_SEGMENT_TREE_UPDATE
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreePairwiseSumV {
  int64_t sum, sumP;
  int cnt;
};

vector<int> dis;

struct CompactSegmentTreePairwiseSum
    : ds::BaseCompactSegmentTree<CompactSegmentTreePairwiseSumV, int, int> {
  using V = CompactSegmentTreePairwiseSumV;
  using InitV = int;
  using Update = int;
  using Node = typename CompactSegmentTreePairwiseSum::Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.sum = res.sumP = res.cnt = 0;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    const auto& v = node.v;
    res.sum += v.sum + v.sumP * res.cnt - res.sumP * v.cnt;
    res.sumP += v.sumP;
    res.cnt += v.cnt;
  }
#endif

  inline void _applyUpdate(const Update& update, Node& node) override {
    auto& v = node.v;
    v.cnt += update;
    v.sum = 0;
    v.sumP = v.cnt ? dis[node.lower] : 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    auto& v = node.v;
    v.cnt = initV;
    v.sum = 0;
    v.sumP = v.cnt ? dis[node.lower] : 0;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto& lv = lNode.v;
    const auto& rv = rNode.v;
    res.sum = lv.sum + rv.sum + rv.sumP * lv.cnt - lv.sumP * rv.cnt;
    res.sumP = lv.sumP + rv.sumP;
    res.cnt = lv.cnt + rv.cnt;
  }
};

struct Query {
  int op, x, y;

  inline Query(int op, int x, int y) : op(op), x(x), y(y) {}
};

int main() {
  int n;
  io::readInt(n);
  vector<int> xs(n);
  FOR(i, 0, n) {
    io::readInt(xs[i]);
  }
  auto xs0 = xs;
  int q;
  io::readInt(q);
  dis.reserve(n + q);
  FOR(i, 0, n) {
    dis.push_back(xs[i]);
  }
  vector<Query> queries;
  queries.reserve(q);
  FOR(i, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    if (op == 1) {
      xs0[--x] += y;
      dis.push_back(xs0[x]);
    }
    queries.emplace_back(op, x, y);
  }
  SORTUNIQUE(dis);
  int m = SIZE(dis);
  vector<int> initVs(m);
  FOR(i, 0, n) {
    xs[i] = INDEX(dis, xs[i]);
    initVs[xs[i]] = 1;
  }
  CompactSegmentTreePairwiseSum st;
  st.init(move(initVs));
  for (auto& query : queries) {
    if (query.op == 1) {
      st.update(xs[query.x], -1);
      xs[query.x] = INDEX(dis, dis[xs[query.x]] + query.y);
      st.update(xs[query.x], 1);
    } else {
      query.x = INDEX(dis, query.x);
      query.y = INDEX(dis, query.y + 1);
      io::writeInt(query.x < query.y ? st.calcRange(query.x, query.y).sum : 0, '\n');
    }
  }
  return 0;
}
