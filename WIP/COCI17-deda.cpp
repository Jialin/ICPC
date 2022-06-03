// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define BASE_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeStops : ds::BaseCompactSegmentTree<int, int, int, pair<int, int>> {
  using V = int;
  using InitV = int;
  using Update = int;
  using TraverseArgs = pair<int, int>;
  using Node = typename CompactSegmentTreeStops::Node;

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.v = update;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = min(lNode.v, rNode.v);
  }

  inline Traverse _traverse(Node& node, int lower, int upper, TraverseArgs& args) override {
    if (args.second >= 0 || node.v > args.first) {
      return Traverse::NONE;
    }
    if (node.isLeaf()) {
      args.second = node.lower + 1;
      return Traverse::NONE;
    }
    int idx = &node - _nodes.data();
    return _nodes[idx << 1].v <= args.first ? Traverse::LEFT : Traverse::RIGHT;
  }

  inline bool _mergeAfterTraverse(TraverseArgs& args) override {
    return false;
  }
};

const int INF = 1000000000 + 1;

char op[2];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  CompactSegmentTreeStops st;
  st.init(vector<int>(n, INF));
  FOR(_, 0, q) {
    int idx;
    io::readCharArray(op);
    if (op[0] == 'M') {
      int cnt;
      io::readInt(cnt);
      io::readInt(idx);
      --idx;
      st.update(idx, cnt);
    } else {
      pair<int, int> args;
      io::readInt(args.first);
      io::readInt(idx);
      --idx;
      args.second = -1;
      st.traverseRange(idx, n, args);
      io::writeInt(args.second, '\n');
    }
  }
  return 0;
}
