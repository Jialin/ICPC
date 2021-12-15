// https://codeforces.com/contest/295/problem/E
#include "ds/treap/base_treap.h"

using namespace std;

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
