// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"
#include "math/mod/add.h"
#include "math/mod/mul.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000 + 1;
const int MOD1 = 1000000007;
const int BASE1 = 31;

int POWS1[MAXN], ONES1[MAXN];

struct LazyCompactSegmentTreeHash : ds::BaseLazyCompactSegmentTree<int, int, int> {
  using V = int;
  using InitV = int;
  using Update = int;
  using Node = typename LazyCompactSegmentTreeHash::Node;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = 0;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    res = math::addMod(math::mulMod(res, POWS1[node.upper - node.lower], MOD1), node.v, MOD1);
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.v = math::mulMod(ONES1[node.upper - node.lower], update, MOD1);
    node.update = update;
  }

  inline void _clearUpdate(Node& node) override {
    node.update = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res =
        math::addMod(math::mulMod(lNode.v, POWS1[rNode.upper - rNode.lower], MOD1), rNode.v, MOD1);
  }
};

char s[MAXN];

int main() {
  int n, q, q2;
  io::readInt(n);
  io::readInt(q);
  io::readInt(q2);
  io::readCharArray(s);
  vector<int> vs(n);
  POWS1[0] = 1;
  ONES1[0] = 0;
  FOR(i, 0, n) {
    POWS1[i + 1] = math::mulMod(POWS1[i], BASE1, MOD1);
    ONES1[i + 1] = math::addMod(math::mulMod(ONES1[i], BASE1, MOD1), 1, MOD1);
    vs[i] = s[i] - '0' + 1;
  }
  LazyCompactSegmentTreeHash st;
  st.init(move(vs));
  q += q2;
  FOR(_, 0, q) {
    int op, lower, upper, v;
    io::readInt(op);
    io::readInt(lower);
    io::readInt(upper);
    io::readInt(v);
    --lower;
    if (op == 1) {
      st.updateRange(lower, upper, v + 1);
    } else {
      io::writeCharArray(
          st.calcRange(lower, upper - v) == st.calcRange(lower + v, upper) ? "YES\n" : "NO\n");
    }
  }
  return 0;
}
