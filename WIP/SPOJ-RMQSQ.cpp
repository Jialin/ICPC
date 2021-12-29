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

namespace ds {

template<typename _V, typename _InitV = _V, typename _Update = _InitV>
struct CompactSegmentTreeMin : BaseCompactSegmentTree<_V, _InitV, _Update> {
  using V = _V;
  using InitV = _InitV;
  using Update = _Update;
  using Node = typename CompactSegmentTreeMin::Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = numeric_limits<V>::max();
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    MMIN(res, node.v);
  }
#endif

  inline void _applyUpdate(const Update& update, Node& node) override {
    assert(false);
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = min(lNode.v, rNode.v);
  }
};

} // namespace ds

struct Query {
  int lower, upper, idx;

  inline Query(int lower, int upper, int idx) : lower(lower), upper(upper), idx(idx) {}
};

int main() {
  int n;
  io::readInt(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  int q;
  io::readInt(q);
  vector<Query> queries;
  queries.reserve(q);
  vector<int> dis;
  dis.reserve((q << 1) | 1);
  dis.push_back(0);
  FOR(i, 0, q) {
    int lower, upper;
    io::readInt(lower);
    io::readInt(upper);
    ++upper;
    queries.emplace_back(lower, upper, i);
    dis.push_back(lower);
    dis.push_back(upper);
  }
  SORTUNIQUE(dis);
  FOR(i, 1, SIZE(dis)) {
    vs[i - 1] = vs[dis[i - 1]];
    FOR(j, dis[i - 1] + 1, dis[i]) {
      MMIN(vs[i - 1], vs[j]);
    }
  }
  vs.erase(vs.begin() + SIZE(dis) - 1, vs.end());
  ds::CompactSegmentTreeMin<int> st;
  st.init(move(vs));
  vector<int> results(q);
  for (const auto& query : queries) {
    results[query.idx] = st.calcRange(INDEX(dis, query.lower), INDEX(dis, query.upper));
  }
  for (auto res : results) {
    io::writeInt(res, '\n');
  }
  return 0;
}
