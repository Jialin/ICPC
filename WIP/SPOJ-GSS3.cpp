// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_UPDATE
#define _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeMaxRangeV {
  int sum, lmax, rmax, res;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const CompactSegmentTreeMaxRangeV& v) {
    o << '{' << tostring2("sum", v.sum, "lmax", v.lmax, "rmax", v.rmax, "res", v.res) << '}';
    return o;
  }
#endif
};

const int INF = 1000000000;

struct CompactSegmentTreeMaxRange
    : ds::BaseCompactSegmentTree<CompactSegmentTreeMaxRangeV, int, int> {
  using V = CompactSegmentTreeMaxRangeV;
  using InitV = int;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentTreeMaxRange::_Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.res = INF;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    auto& v = node.v;
    if (res.res == INF) {
      res.res = v.res;
      res.rmax = v.rmax;
      return;
    }
    MMAX(res.res, max(v.res, res.rmax + v.lmax));
    res.rmax = max(res.rmax + v.sum, v.rmax);
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  inline void _updateV(const Update& update, Node& node) override {
    _initV(update, node);
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    auto& v = node.v;
    v.sum = v.lmax = v.rmax = v.res = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res.res = max(max(lv.res, rv.res), lv.rmax + rv.lmax);
    res.sum = lv.sum + rv.sum;
    res.lmax = max(lv.lmax, lv.sum + rv.lmax);
    res.rmax = max(lv.rmax + rv.sum, rv.rmax);
  }
};

int main() {
  int n;
  io::readInt(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  CompactSegmentTreeMaxRange st;
  st.init(move(vs));
  DEBUGV(st);
  int q;
  io::readInt(q);
  CompactSegmentTreeMaxRangeV res;
  FOR(_, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    --x;
    if (op) {
      st._clearV(res);
      st._calcRange(0, x, y, res);
      io::writeInt(res.res, '\n');
    } else {
      st.update(x, y);
    }
  }
  return 0;
}
