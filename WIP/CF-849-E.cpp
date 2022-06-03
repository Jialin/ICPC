// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define BASE_COMPACT_SEGMENT_TREE_UPDATE
#include "ds/segment_tree/base_compact_segment_tree_macros.h"
#define BASE_TREAP_FOREST_CALC_SUFFIX
#define BASE_TREAP_FOREST_ERASE
#define BASE_TREAP_FOREST_RESERVE_ROOTS
#define BASE_TREAP_FOREST_UPDATE
#define BASE_TREAP_RESERVE_NODES
#include "ds/treap/base_treap_forest_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "ds/treap/base_treap_forest.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

template<typename V, typename KEY = int>
struct TreapForestSum : ds::BaseTreapForest<V, V, KEY> {
  using NodeV = V;
  using RangeV = V;
  using Node = typename TreapForestSum::_Node;

  inline void _initRangeV(RangeV& res) override {
    res = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& nodeV) override {
    node._v = nodeV;
    node._rangeV = nodeV;
  }

  inline void _updateAllVs(Node& node, const NodeV& delta) override {
    node._v += delta;
    node._rangeV += delta;
  }

  inline RangeV _calcRangeV(int idx) {
    return idx < 0 ? 0 : this->_nodes[idx]._rangeV;
  }

  inline void _mergeRangeV(Node& node) override {
    node._rangeV = _calcRangeV(node._lIdx) + node._v + _calcRangeV(node._rIdx);
  }

#ifdef _BASE_TREAP_CALC_APPEND
  inline void _appendNode(RangeV& res, const Node& node) override {
    res += node._v;
  }

  inline void _appendRange(RangeV& res, const Node& node) override {
    res += node._rangeV;
  }
#endif
};

TreapForestSum<int64_t> treap;
int UPDATE_KEY, UPDATE_V;

struct CompactSegmentTreeTreap : ds::BaseCompactSegmentTree<int, nullptr_t, nullptr_t, int64_t> {
  using V = int;
  using InitV = nullptr_t;
  using Update = nullptr_t;
  using TraverseArgs = int64_t;
  using Node = typename CompactSegmentTreeTreap::Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  inline Traverse _traverse(Node& node, int lower, int upper, TraverseArgs& args) override {
    args += treap.calcSuffix(lower, node.v);
    return Traverse::NONE;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  inline bool _mergeAfterTraverse(TraverseArgs& args) override {
    return false;
  }
#endif

  inline void updateTreap(int idx) {
    if (UPDATE_V < 0) {
      treap.erase(UPDATE_KEY, idx);
    } else {
      treap.update(UPDATE_KEY, UPDATE_V, idx);
    }
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    updateTreap(node.v);
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = &node - _nodes.data();
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = lNode.v >> 1;
    updateTreap(res);
  }
};

const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXBIT = 17;
const int MAXNODE = MAXBIT * MAXQ << 2;

set<int> idxLookups[MAXN + 1];
CompactSegmentTreeTreap st;

inline void updateST(int idx, int key, int v) {
  UPDATE_KEY = key;
  UPDATE_V = v;
  st.update(idx, nullptr);
}

// ...ooooo
// ...ooooo
// ...ooooo
// ...xoooo
// ........
// ........
//
// update (i,j) affects all ii<=i and j<=jj
//

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  treap.init(math::nextPow2_32(n) << 1);
  treap.reserveNodes(MAXNODE);
  UPDATE_V = -1;
  st.init(vector<nullptr_t>(n));
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
    auto& lookup = idxLookups[vs[i]];
    if (!lookup.empty()) {
      const auto it = lookup.rbegin();
      updateST(i, *it, i - *it);
    }
    lookup.insert(lookup.end(), i);
  }
  FOR(_, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    --x;
    if (op == 1 && vs[x] != y) {
      {
        auto& lookup = idxLookups[vs[x]];
        auto it = lookup.find(x);
        int prev = -1;
        if (it != lookup.begin()) {
          auto jt = it;
          --jt;
          prev = *jt;
          updateST(x, prev, -1);
        }
        auto jt = it;
        ++jt;
        if (jt != lookup.end()) {
          updateST(*jt, x, -1);
          if (prev >= 0) {
            updateST(*jt, prev, *jt - prev);
          }
        }
        lookup.erase(it);
      }
      {
        auto& lookup = idxLookups[y];
        auto it = lookup.lower_bound(x);
        if (it != lookup.begin()) {
          auto jt = it;
          --jt;
          if (it != lookup.end()) {
            updateST(*it, *jt, -1);
          }
          updateST(x, *jt, x - *jt);
        }
        if (it != lookup.end()) {
          updateST(*it, x, *it - x);
        }
        lookup.insert(it, x);
      }
      vs[x] = y;
    } else if (op == 2) {
      int64_t res = 0;
      st.traverseRange(x, y, res);
      io::writeInt(res, '\n');
    }
  }
  return 0;
}
