// https://codeforces.com/contest/295/problem/E
#include "ds/treap/base_treap.h"

using namespace std;

struct TreapPairwiseGapNode {
  int cnt;
  int64_t xSum, oddSum, sum;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const TreapPairwiseGapNode& node) {
    o << "[cnt:" << node.cnt << " sum:" << node.sum << " xSum:" << node.xSum << "]";
    return o;
  }
#endif
};

struct TreapPairwiseGap : ds::BaseTreap<nullptr_t, TreapPairwiseGapNode, int> {
  using _Node = typename TreapPairwiseGap::_Node;

  inline void _initRangeV(TreapPairwiseGapNode& res) override {
    res.cnt = 0;
    res.xSum = 0;
    res.oddSum = 0;
    res.sum = 0;
  }

  inline void _initV(_Node& node) override {
    _initRangeV(node._rangeV);
  }

  inline void _updateV(_Node& node, const nullptr_t& delta) override {
    _mergeRangeV(node);
  }

  inline void _mergeRangeV(_Node& node) override {
    auto& range = node._rangeV;
    _initRangeV(range);
    if (node._lIdx >= 0) {
      _appendRange(range, this->_nodes[node._lIdx]);
    }
    _appendNode(range, node);
    if (node._rIdx >= 0) {
      _appendRange(range, this->_nodes[node._rIdx]);
    }
  }

  inline void _appendNode(TreapPairwiseGapNode& res, const _Node& node) override {
    res.sum += res.cnt * (node._key + 0LL) - res.xSum;
    res.xSum += node._key;
    res.oddSum += ((res.cnt << 1) | 1LL) * node._key;
    ++res.cnt;
  }

  inline void _appendRange(TreapPairwiseGapNode& res, const _Node& node) override {
    const auto& range = node._rangeV;
    res.sum += (res.cnt - range.cnt) * range.xSum - res.xSum * range.cnt + range.oddSum;
    res.xSum += range.xSum;
    res.oddSum += range.oddSum + range.xSum * (res.cnt << 1);
    res.cnt += range.cnt;
  }
};
