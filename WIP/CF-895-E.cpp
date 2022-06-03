// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct SumSegmentTree : ds::BaseLazyCompactSegmentTree<double, int, pair<double, double>> {
  using V = double;
  using InitV = int;
  using Update = pair<double, double>;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = 0;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    res += node.v;
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return true;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.update.first *= update.first;
    node.update.second = node.update.second * update.first + update.second;
    node.v = node.v * update.first + update.second * (node.upper - node.lower);
  }

  inline void _clearUpdate(Node& node) override {
    node.update.first = 1;
    node.update.second = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = lNode.v + rNode.v;
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
  SumSegmentTree st;
  st.init(move(vs));
  FOR(_, 0, q) {
    int op, lower, upper;
    io::readInt(op);
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    double res = st.calcRange(lower, upper);
    if (op == 1) {
      int lower2, upper2;
      io::readInt(lower2);
      io::readInt(upper2);
      --lower2;
      int size = upper - lower, size2 = upper2 - lower2;
      res /= size;
      double res2 = st.calcRange(lower2, upper2) / size2;
      st.updateRange(lower, upper, {(size - 1.0) / size, res2 / size});
      st.updateRange(lower2, upper2, {(size2 - 1.0) / size2, res / size2});
    } else {
      printf("%.10lf\n", res);
    }
  }
  return 0;
}
