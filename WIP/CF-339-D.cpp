// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_UPDATE
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeOrXorV {
  int v;
  bool useOr;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const CompactSegmentTreeOrXorV& v) {
    return o << '{' << tostring2("v", v.v, "useOr", v.useOr) << '}';
  }
#endif
};

struct CompactSegmentTreeOrXor : ds::BaseCompactSegmentTree<CompactSegmentTreeOrXorV, int> {
  using V = CompactSegmentTreeOrXorV;
  using InitV = int;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentTreeOrXor::_Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    assert(false);
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    assert(false);
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  inline void _updateV(const Update& update, Node& node) override {
    node.v.v = update;
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    auto& v = node.v;
    v.v = initV;
    v.useOr = false;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res.useOr = !lv.useOr;
    res.v = res.useOr ? (lv.v | rv.v) : (lv.v ^ rv.v);
  }
};

int main() {
  int bit, q;
  io::readInt(bit);
  io::readInt(q);
  int n = 1 << bit;
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  CompactSegmentTreeOrXor st;
  st.init(move(vs));
  CompactSegmentTreeOrXorV update;
  FOR(_, 0, q) {
    int idx, v;
    io::readInt(idx);
    io::readInt(v);
    st.update(idx - 1, v);
    io::writeInt(st._nodes[0].v.v, '\n');
  }
  return 0;
}
