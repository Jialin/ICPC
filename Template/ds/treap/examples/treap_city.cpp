// https://codeforces.com/contest/167/problem/D
#include "ds/treap/base_treap.h"

using namespace std;

struct TreapCityRange {
  int unused, result;
};

struct TreapCity : ds::BaseTreap<int, TreapCityRange, int> {
  using NodeV = int;
  using RangeV = TreapCityRange;
  using Node = TreapCity::_Node;

  inline void _initRangeV(RangeV& res) override {
    res.unused = 0;
    res.result = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& v) override {
    node._priority = v;
  }

  inline void _updateAllVs(Node& node, const NodeV& delta) override {
    _initRangeV(node._rangeV);
  }

  inline int getUnused(int idx) {
    return idx >= 0 ? _nodes[idx]._rangeV.unused : 0;
  }

  inline int getResult(int idx) {
    return idx >= 0 ? _nodes[idx]._rangeV.result : 0;
  }

  inline void _mergeRangeV(Node& node) override {
    auto& rangeV = node._rangeV;
    int used = 0;
    if (node._lIdx >= 0) {
      used = max(used, getUnused(node._lIdx) + getResult(node._rIdx) + 1);
    }
    if (node._rIdx >= 0) {
      used = max(used, getResult(node._lIdx) + getUnused(node._rIdx) + 1);
    }
    rangeV.unused = getResult(node._lIdx) + getResult(node._rIdx);
    rangeV.result = max(used, rangeV.unused);
  }
};
