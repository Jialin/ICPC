// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_ERASE
#define BASE_TREAP_INIT_ORDERED_ITEMS
#define BASE_TREAP_RESERVE_NODES
#define BASE_TREAP_UPDATE
#define _BASE_TREAP_CALC_RANGE
#define _BASE_TREAP_SIZE
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/base_treap.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct TreapPairwiseGapRangeV {
  int cnt;
  int64_t sum, sum2;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const TreapPairwiseGapRangeV& node) {
    o << "[sum: " << node.sum << " sum2:" << node.sum2 << "]";
    return o;
  }
#endif
};

struct TreapPairwiseGap : ds::BaseTreap<nullptr_t, TreapPairwiseGapRangeV, int> {
  using NodeV = nullptr_t;
  using RangeV = TreapPairwiseGapRangeV;
  using Node = typename TreapPairwiseGap::_Node;

  inline void _initRangeV(RangeV& rangeV) override {
    rangeV.cnt = 0;
    rangeV.sum = 0;
    rangeV.sum2 = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& v) override {
    auto& rangeV = node._rangeV;
    rangeV.sum = node._key;
    rangeV.sum2 = 0;
  }

  inline void _updateAllVs(Node& node, const NodeV& delta) override {
    assert(false);
  }

  inline int64_t _calcSum(int idx) {
    return idx >= 0 ? _nodes[idx]._rangeV.sum : 0;
  }

  inline int64_t _calcSum2(int idx) {
    return idx >= 0 ? _nodes[idx]._rangeV.sum2 : 0;
  }

  inline void _mergeRangeV(Node& node) override {
    auto& rangeV = node._rangeV;
    int lIdx = node._lIdx, rIdx = node._rIdx;
    rangeV.sum = _calcSum(lIdx) + node._key + _calcSum(rIdx);
    rangeV.sum2 = _calcSum2(lIdx) + _calcSum2(rIdx) +
                  (_calcSum(rIdx) + node._key) * _calcSize(lIdx) -
                  (_calcSum(lIdx) + node._key) * _calcSize(rIdx) + _calcSum(rIdx) - _calcSum(lIdx);
  }

#ifdef _BASE_TREAP_CALC_APPEND
  inline void _appendNode(RangeV& res, const Node& node) override {
    res.sum2 += node._key * CAST<int64_t>(res.cnt) - res.sum;
    ++res.cnt;
    res.sum += node._key;
  }

  inline void _appendRange(RangeV& res, const Node& node) override {
    res.sum2 += node._rangeV.sum2 + node._rangeV.sum * res.cnt - res.sum * node._size;
    res.cnt += node._size;
    res.sum += node._rangeV.sum;
  }
#endif
};

int main() {
  int n;
  io::readInt(n);
  vector<int> as(n);
  vector<pair<int, nullptr_t>> initItems(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
    initItems[i].first = as[i];
  }
  TreapPairwiseGap treap;
  treap.reserveNodes(n);
  sort(ALL(initItems), [](const auto& l, const auto& r) {
    return l.first < r.first;
  });
  treap.initOrderedItems(initItems);
  int q;
  io::readInt(q);
  TreapPairwiseGapRangeV resRangeV;
  FOR(_, 0, q) {
    int op, x, y;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    if (op == 1) {
      --x;
      treap.erase(as[x]);
      as[x] += y;
      treap.update(as[x], nullptr);
    } else {
      treap._calcRange(treap._roots[0], x, y + 1, resRangeV);
      io::writeInt(resRangeV.sum2);
      io::writeChar('\n');
    }
  }
  return 0;
}
