// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_UPDATE
#define BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentCountDistinct : ds::BaseCompactSegmentTree<int> {
  using V = int;
  using InitV = int;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentCountDistinct::_Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = 0;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    res |= node.v;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  inline void _updateV(const Update& update, Node& node) override {
    node.v = update;
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res = lv | rv;
  }
};

const int MAXN = 100000 + 1;

char s[MAXN];

int main() {
  int n = io::readCharArray(s);
  vector<int> vs(n);
  FOR(i, 0, n) {
    vs[i] = 1 << (s[i] - 'a');
  }
  CompactSegmentCountDistinct st;
  st.init(move(vs));
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    int op;
    io::readInt(op);
    if (op == 1) {
      int idx;
      char c[2];
      io::readInt(idx);
      io::readCharArray(c);
      st.update(idx - 1, 1 << (c[0] - 'a'));
    } else {
      int lower, upper;
      io::readInt(lower);
      io::readInt(upper);
      io::writeInt(__builtin_popcount(st.calcRange(lower - 1, upper)), '\n');
    }
  }
  return 0;
}
