// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_TREAP_INIT_ORDERED_VALUES
#define BASE_LAZY_TREAP_MERGE3
#define BASE_LAZY_TREAP_RESERVE_NODES
#define BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH
#define BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH
#include "ds/treap/base_lazy_treap_macros.h"

#include "ds/treap/base_lazy_treap.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct LazyTreapReverseFlipSum
    : ds::BaseLazyTreap<pair<int, int>, bool, pair<int64_t, int64_t>, int> {
  using NodeV = pair<int, int>;
  using UpdateV = bool;
  using RangeV = pair<int64_t, int64_t>;
  using Node = typename LazyTreapReverseFlipSum::_Node;

  inline void _initRangeV(RangeV& rangeV) override {
    rangeV.first = 0;
    rangeV.second = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& nodeV) override {
    node._v = nodeV;
    node._updateV = false;
    node._rangeV.first = nodeV.first;
    node._rangeV.second = nodeV.second;
  }

  inline void _pushUpdate(UpdateV& updateV, const UpdateV& srcUpdateV) override {
    updateV ^= srcUpdateV;
  }

  inline int64_t _calcRangeVFlip(int idx, bool flip) {
    if (idx < 0) {
      return 0;
    }
    const auto& node = _nodes[idx];
    return (flip ^ node._updateV) ? node._rangeV.second : node._rangeV.first;
  }

  inline void _mergeRangeV(_Node& node) override {
    node._rangeV.first =
        _calcRangeVFlip(node._lIdx, false) + node._v.first + _calcRangeVFlip(node._rIdx, false);
    node._rangeV.second =
        _calcRangeVFlip(node._lIdx, true) + node._v.second + _calcRangeVFlip(node._rIdx, true);
  }

  inline void _pushAndClearUpdate(_Node& node) override {
    if (node._updateV) {
      node._updateV = false;
      swap(node._lIdx, node._rIdx);
      swap(node._v.first, node._v.second);
      swap(node._rangeV.first, node._rangeV.second);
      if (node._lIdx >= 0) {
        _nodes[node._lIdx]._updateV ^= true;
      }
      if (node._rIdx >= 0) {
        _nodes[node._rIdx]._updateV ^= true;
      }
    }
  }
};

LazyTreapReverseFlipSum treap;

inline int64_t calcRange(int& idx, int lower, int upper) {
  if (idx < 0 || upper - lower < 1) {
    return 0;
  }
  int lIdx, mIdx, rIdx;
  treap.splitRangeByKth(lower, upper, lIdx, mIdx, rIdx);
  auto res = treap._calcRangeVFlip(mIdx, false);
  treap.merge3(lIdx, mIdx, rIdx);
  return res;
}

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  vector<pair<int, int>> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i].first);
  }
  FOR(i, 0, n) {
    io::readInt(vs[i].second);
  }
  treap.reserveNodes(n);
  treap.initOrderedValues(vs);
  int minusCnt = 0;
  FOR(_, 0, m) {
    int op;
    io::readInt(op);
    if (op == 1) {
      int lower, upper;
      io::readInt(lower);
      io::readInt(upper);
      --lower;
      treap.updateRangeByKth(lower, upper, true);
    } else if (op == 2) {
      int k;
      io::readInt(k);
      minusCnt = k - minusCnt;
    } else {
      int x1, y1, x2, y2;
      io::readInt(x1);
      io::readInt(y1);
      io::readInt(x2);
      io::readInt(y2);
      --x1;
      --x2;
      auto res = calcRange(treap._roots[0], x1, y1);
      if (minusCnt <= x2) {
      } else if (y2 <= minusCnt) {
        res = -res;
      } else {
        res -= calcRange(treap._roots[0], x1, x1 + minusCnt - x2) << 1;
      }
      io::writeInt(res);
      io::writeChar('\n');
    }
  }
  return 0;
}
