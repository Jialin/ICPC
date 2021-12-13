// !macro_gen
// ALL TREAP_SET_ALL
#pragma once

#include "ds/treap/base_treap_macros.h" // INCLUDE

#include "ds/treap/base_treap.h"

namespace ds {

template<typename KEY = int>
struct TreapSet : BaseTreap<nullptr_t, int, KEY> {
#ifdef TREAP_SET_INSERT // ^
  inline void insert(const KEY& key) {
    // TREAP_SET_INSERT => BASE_TREAP_UPDATE
    this->update(key, nullptr);
  }
#endif

  using NodeV = nullptr_t;
  // TODO: move most of the logic as `size`
  using RangeV = int;
  using Node = typename TreapSet::_Node;

  inline void _initRangeV(RangeV& res) override {
    res = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& nodeV) override {
    node._rangeV = 1;
  }

  inline void _updateAllVs(Node& node, const NodeV& delta) override {
    _mergeRangeV(node);
  }

  inline void _mergeRangeV(Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + 1 +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

#ifdef _BASE_TREAP_CALC_APPEND
  inline void _appendNode(RangeV& res, const Node& node) override {
    ++res;
  }

  inline void _appendRange(RangeV& res, const Node& node) override {
    res += node._rangeV;
  }
#endif
};

} // namespace ds
