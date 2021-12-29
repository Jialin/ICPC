// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_COMPACT_SEGMENT_TREE_INIT
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

namespace ds {

template<typename _V, typename _InitV = _V, typename _Update = _InitV>
struct CompactSegmentTreeMax : BaseCompactSegmentTree<_V, _InitV, _Update> {
  using V = _V;
  using InitV = _InitV;
  using Update = _Update;
  using Node = typename CompactSegmentTreeMax::Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = numeric_limits<V>::min();
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    MMAX(res, node.v);
  }
#endif

  inline void _applyUpdate(const Update& update, Node& node) override {
    assert(false);
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = max(lNode.v, rNode.v);
  }
};

} // namespace ds

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  vector<int> hs(n);
  FOR(i, 0, n) {
    io::readInt(hs[i]);
  }
  ds::CompactSegmentTreeMax<int> st;
  st.init(hs);
  int res = 0;
  FOR(i, 0, m) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    if (l > r) {
      swap(l, r);
    }
    if (l + 1 >= r) {
      ++res;
      continue;
    }
    if (hs[l - 1] >= st.calcRange(l, r - 1)) {
      ++res;
    }
  }
  io::writeInt(res);
  io::writeChar('\n');
}
