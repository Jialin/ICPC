// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_RESERVE
#define _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/gcd/gcd32.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeMinCntGcdV {
  int d, cnt;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const CompactSegmentTreeMinCntGcdV& v) {
    o << "{d:" << v.d << ",cnt:" << v.cnt << '}';
    return o;
  }
#endif
};

struct CompactSegmentTreeMinCntGcd : ds::BaseCompactSegmentTree<CompactSegmentTreeMinCntGcdV, int> {
  using V = CompactSegmentTreeMinCntGcdV;
  using InitV = int;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentTreeMinCntGcd::_Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.d = 0;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    const auto& v = node.v;
    int resD = res.d ? math::gcd32(res.d, v.d) : v.d;
    if (resD != res.d) {
      res.cnt = 0;
    }
    if (resD == v.d) {
      res.cnt += v.cnt;
    }
    res.d = resD;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  inline void _updateV(const Update& update, Node& node) override {
    assert(false);
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    auto& v = node.v;
    v.d = initV;
    v.cnt = 1;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res.d = math::gcd32(lv.d, rv.d);
    res.cnt = (lv.d == res.d ? lv.cnt : 0) + (rv.d == res.d ? rv.cnt : 0);
  }
};

int main() {
  int n;
  io::readInt(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  CompactSegmentTreeMinCntGcd st;
  st.reserve(n);
  st.init(move(vs));
  int q;
  io::readInt(q);
  CompactSegmentTreeMinCntGcdV res;
  FOR(_, 0, q) {
    int lower, upper;
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    st._clearV(res);
    st._calcRange(0, lower, upper, res);
    io::writeInt(upper - lower - res.cnt);
    io::writeChar('\n');
  }
  return 0;
}
