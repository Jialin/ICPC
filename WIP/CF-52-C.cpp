// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#define _BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

template<typename V, typename InitV = V, typename Update = InitV>
struct LazyCompactSegmentTreeMin : ds::BaseLazyCompactSegmentTree<V, InitV, Update> {
  using Node = typename LazyCompactSegmentTreeMin::_Node;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V // ^
  inline void _clearV(V& res) override {
    res = numeric_limits<V>::max();
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V // ^
  inline void _appendV(const Node& node, V& res) override {
    MMIN(res, getMin(node));
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.update += update;
  }

  inline void _clearUpdate(Node& node) override {
    node.update = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline V getMin(const Node& node) {
    return node.v + node.update;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = min(getMin(lNode), getMin(rNode));
  }
};

int main() {
  int n;
  io::readInt(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  LazyCompactSegmentTreeMin<int64_t, int, int64_t> st;
  st.init(move(vs));
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    int lower, upper;
    io::readInt(lower);
    io::readInt(upper);
    ++upper;
    char c = io::readChar();
    if (c == ' ') {
      int v;
      io::readInt(v);
      if (lower < upper) {
        st.updateRange(lower, upper, v);
      } else {
        st.updateRange(lower, n, v);
        st.updateRange(0, upper, v);
      }
    } else {
      int64_t res = numeric_limits<int64_t>::max();
      if (lower < upper) {
        st._calcRange(0, lower, upper, res);
      } else {
        st._calcRange(0, lower, n, res);
        st._calcRange(0, 0, upper, res);
      }
      io::writeInt(res, '\n');
    }
  }
  return 0;
}
