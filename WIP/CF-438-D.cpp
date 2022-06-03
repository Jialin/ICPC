// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#define _BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#define _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct LazyCompactSegmentTreeModRangeSetSingleV {
  int cnt, max1, max2;
  int64_t sum;

  inline void init(int v) {
    cnt = 1;
    sum = max1 = v;
    max2 = numeric_limits<int>::min();
  }

#ifdef LOCAL
  inline friend ostream&
  operator<<(ostream& o, const LazyCompactSegmentTreeModRangeSetSingleV& node) {
    o << tostring2("cnt", node.cnt, "max1", node.max1, "max2", node.max2, "sum", node.sum);
    return o;
  }
#endif
};

struct LazyCompactSegmentTreeModRangeSetSingle
    : ds::BaseLazyCompactSegmentTree<LazyCompactSegmentTreeModRangeSetSingleV, int, int, int> {
  using V = LazyCompactSegmentTreeModRangeSetSingleV;
  using InitV = int;
  using Update = int;
  using TraverseArgs = int;
  using Node = typename LazyCompactSegmentTreeModRangeSetSingle::_Node;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE // ^
  inline Traverse _traverse(Node& node, int lower, int upper, TraverseArgs& args) override {
    auto& v = node.v;
    if (v.max1 < args) {
      return Traverse::NONE;
    }
    if (node.lower < lower || upper < node.upper) {
      return Traverse::ALL;
    }
    if (node.lower + 1 < node.upper) {
      int idx = &node - _nodes.data();
      int rIdx = idx + node.lSize();
      _pushNode(node, _nodes[idx + 1]);
      _pushNode(node, _nodes[rIdx]);
    }
    int newMax1 = v.max1 % args;
    if (newMax1 > v.max2) {
      v.sum -= CAST<int64_t>(v.max1 - newMax1) * v.cnt;
      v.max1 = newMax1;
      return Traverse::NONE;
    }
    return Traverse::ALL;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V // ^
  inline void _clearV(V& res) override {
    res.sum = 0;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V // ^
  inline void _appendV(const Node& node, V& res) override {
    res.sum += node.v.sum;
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return true;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.v.init(update);
  }

  inline void _clearUpdate(Node& node) override {}

  inline void _initV(InitV initV, Node& node) override {
    node.v.init(initV);
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res.sum = lv.sum + rv.sum;
    res.max1 = max(lv.max1, rv.max1);
    res.max2 = max(lv.max2, rv.max2);
    res.cnt = 0;
    if (res.max1 == lv.max1) {
      res.cnt += lv.cnt;
    } else {
      MMAX(res.max2, lv.max1);
    }
    if (res.max1 == rv.max1) {
      res.cnt += rv.cnt;
    } else {
      MMAX(res.max2, rv.max1);
    }
  }

  inline void _pushNode(const Node& parent, Node& node) override {
    auto& v = node.v;
    const auto& pv = parent.v;
    if (v.max1 > pv.max1) {
      v.sum -= CAST<int64_t>(v.max1 - pv.max1) * v.cnt;
      v.max1 = pv.max1;
    }
  }
};

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  LazyCompactSegmentTreeModRangeSetSingle st;
  st.init(move(vs));
  LazyCompactSegmentTreeModRangeSetSingleV res;
  // DEBUGV(st);
  FOR(_, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    --x;
    if (op == 1) {
      st._clearV(res);
      st._calcRange(0, x, y, res);
      io::writeInt(res.sum, '\n');
    } else if (op == 2) {
      int v;
      io::readInt(v);
      st.traverse(x, y, v);
    } else {
      st.updateRange(x, x + 1, y);
    }
  }
  return 0;
}
