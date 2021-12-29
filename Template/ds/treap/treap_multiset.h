// !macro_gen
// ALL TREAP_MULTISET_ALL
#pragma once

#include "ds/treap/base_treap_macros.h" // INCLUDE
#include "ds/treap/treap_multiset_macros.h"

#include "ds/treap/base_treap.h"

namespace ds {

template<typename KEY = int>
struct TreapMultiset : BaseTreap<int, int, KEY> {
#ifdef TREAP_MULTISET_INSERT // ^
  inline void insert(const KEY& key) {
    // TREAP_MULTISET_INSERT => BASE_TREAP_UPDATE
    this->update(key, 1);
  }
#endif

  using NodeV = int;
  using RangeV = int;
  using Node = typename TreapMultiset::_Node;

  inline void _initRangeV(RangeV& rangeV) override {
    rangeV = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& v) override {
    node._v = v;
    node._rangeV = v;
  }

  inline void _updateAllVs(Node& node, const NodeV& delta) override {
    int delta0 = max(delta, -node._v);
    node._v += delta0;
    node._rangeV += delta0;
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
