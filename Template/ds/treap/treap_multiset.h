// !macro_gen
// ALL TREAP_MULTISET_ALL
#pragma once

#include "ds/treap/base_treap_macros.h" // INCLUDE

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

  using _Node = typename TreapMultiset::_Node;

  inline void _initRangeV(int& res) override {
    res = 0;
  }

  inline void _initV(_Node& node) override {
    node._v = 0;
    node._rangeV = 0;
  }

  inline void _updateV(_Node& node, const int& delta) override {
    int delta0 = max(delta, -node._v);
    node._v += delta0;
    node._rangeV += delta0;
  }

  inline void _mergeRangeV(_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + node._v +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

  inline void _appendNode(int& res, const _Node& node) override {
    res += node._v;
  }

  inline void _appendRange(int& res, const _Node& node) override {
    res += node._rangeV;
  }
};

} // namespace ds
