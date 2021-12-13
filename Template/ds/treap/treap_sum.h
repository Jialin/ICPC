#pragma once

#include "ds/treap/base_treap.h"

namespace ds {

template<typename V, typename KEY = int>
struct TreapSum : BaseTreap<V, V, KEY> {
  using NodeV = V;
  using RangeV = V;
  using Node = typename TreapSum::_Node;

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

} // namespace ds
