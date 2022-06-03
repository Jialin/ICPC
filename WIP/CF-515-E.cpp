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

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeMinMaxV {
  int64_t minV, maxV, res;

  inline CompactSegmentTreeMinMaxV() {}

  inline CompactSegmentTreeMinMaxV(int64_t minV, int64_t maxV) : minV(minV), maxV(maxV), res(0) {}

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const CompactSegmentTreeMinMaxV& v) {
    return o << '{' << tostring2("minV", v.minV, "maxV", v.maxV, "res", v.res) << '}';
  }
#endif
};

struct CompactSegmentTreeMinMax : ds::BaseCompactSegmentTree<CompactSegmentTreeMinMaxV> {
  using V = CompactSegmentTreeMinMaxV;
  using InitV = CompactSegmentTreeMinMaxV;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentTreeMinMax::_Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.res = -1;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    const auto& v = node.v;
    if (res.res < 0) {
      res = v;
      return;
    }
    MMAX(res.res, max(v.res, v.maxV - res.minV));
    MMIN(res.minV, v.minV);
    MMAX(res.maxV, v.maxV);
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  inline void _updateV(Node& node, const V& update) override {
    assert(false);
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    node.v = move(initV);
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res.minV = min(lv.minV, rv.minV);
    res.maxV = max(lv.maxV, rv.maxV);
    res.res = max(max(lv.res, rv.res), rv.maxV - lv.minV);
  }
};

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> ds(n), hs(n);
  FOR(i, 0, n) {
    io::readInt(ds[i]);
  }
  FOR(i, 0, n) {
    io::readInt(hs[i]);
  }
  vector<CompactSegmentTreeMinMaxV> vs;
  vs.reserve(n);
  int64_t x = 0;
  FOR(i, 0, n) {
    vs.emplace_back(x - (hs[i] << 1), x + (hs[i] << 1));
    x += ds[i];
  }
  CompactSegmentTreeMinMax st;
  st.reserve(n);
  st.init(move(vs));
  CompactSegmentTreeMinMaxV res1, res2;
  FOR(_, 0, q) {
    int lower, upper;
    io::readInt(lower);
    --lower;
    io::readInt(upper);
    st._clearV(res1);
    int64_t res;
    if (lower <= upper) {
      if (upper == n) {
        st._calcRange(0, 0, lower, res1);
        res = res1.res;
      } else if (!lower) {
        st._calcRange(0, upper, n, res1);
        res = res1.res;
      } else {
        st._calcRange(0, upper, n, res1);
        st._clearV(res2);
        st._calcRange(0, 0, lower, res2);
        res = max(max(res1.res, res2.res), res2.maxV + x - res1.minV);
      }
    } else {
      st._calcRange(0, upper, lower, res1);
      res = res1.res;
    }
    io::writeInt(res, '\n');
  }
  return 0;
}
