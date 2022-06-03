// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeMaxRange : ds::BaseCompactSegmentTree<int> {
  using V = int;
  using InitV = int;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentTreeMaxRange::_Node;

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
    assert(false);
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = max(lNode.v, rNode.v);
  }

  inline int dfs(int idx, int delta) {
    auto& node = _nodes[idx];
    if (node.lower + 1 == node.upper) {
      node.v -= delta;
      return node.lower + 1;
    }
    int rIdx = idx + node.lSize();
    int res = _nodes[idx + 1].v >= delta ? dfs(idx + 1, delta) : dfs(rIdx, delta);
    _mergeV(_nodes[idx + 1], _nodes[rIdx], node.v);
    return res;
  }
};

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> hs(n);
  FOR(i, 0, n) {
    io::readInt(hs[i]);
  }
  CompactSegmentTreeMaxRange st;
  st.init(move(hs));
  FOR(i, 0, q) {
    int delta;
    io::readInt(delta);
    io::writeInt(st._nodes[0].v < delta ? 0 : st.dfs(0, delta), i + 1 == q ? '\n' : ' ');
  }
  return 0;
}
