// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define _BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

vector<int> luckyVs{4,    7,    44,   47,   74,   77,   444,  447,  474,       477,  744,
                    747,  774,  777,  4444, 4447, 4474, 4477, 4744, 4747,      4774, 4777,
                    7444, 7447, 7474, 7477, 7744, 7747, 7774, 7777, 1000000000};
vector<int> nextLuckyIndexs;

struct LazyCompactSegmentTreeLucky : ds::BaseLazyCompactSegmentTree<pair<int, int>, int, int, int> {
  using V = pair<int, int>;
  using InitV = int;
  using Update = int;
  using TraverseArgs = int;
  using Node = typename LazyCompactSegmentTreeLucky::Node;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  inline Traverse _traverse(Node& node, int lower, int upper, TraverseArgs& args) override {
    if (node.v.first >= args) {
      node.v.first -= args;
      node.update += args;
      return Traverse::NONE;
    }
    if (node.isLeaf()) {
      int& idx = nextLuckyIndexs[node.lower];
      int actualV = luckyVs[idx] - node.v.first + args;
      for (++idx; luckyVs[idx] < actualV; ++idx) {}
      node.v.first = luckyVs[idx] - actualV;
      return Traverse::NONE;
    }
    return Traverse::ALL;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.first = numeric_limits<int>::max();
    res.second = 0;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    if (res.first > node.v.first) {
      res = node.v;
    } else if (res.first == node.v.first) {
      res.second += node.v.second;
    }
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.v.first -= update;
    node.update += update;
  }

  inline void _clearUpdate(Node& node) override {
    node.update = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v.first = initV;
    node.v.second = 1;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto& lv = lNode.v;
    const auto& rv = rNode.v;
    if (lv.first == rv.first) {
      res.first = lv.first;
      res.second = lv.second + rv.second;
    } else {
      res = min(lv, rv);
    }
  }
};

char op[7];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  nextLuckyIndexs.resize(n);
  vector<int> gaps(n);
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    int idx = INDEX(luckyVs, v);
    nextLuckyIndexs[i] = idx;
    gaps[i] = luckyVs[idx] - v;
  }
  LazyCompactSegmentTreeLucky st;
  st.init(move(gaps));
  pair<int, int> res;
  FOR(_, 0, q) {
    int lower, upper;
    io::readCharArray(op);
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    if (op[0] == 'c') {
      res.first = numeric_limits<int>::max();
      st._calcRange(lower, upper, res);
      io::writeInt(res.first ? 0 : res.second, '\n');
    } else {
      int delta;
      io::readInt(delta);
      st.traverseRange(lower, upper, delta);
    }
  }
  return 0;
}
