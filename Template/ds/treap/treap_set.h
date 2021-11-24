#pragma once

#define BASE_TREAP_UPDATE
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/base_treap.h"

namespace ds {

template<typename KEY = int>
struct TreapSet : BaseTreap<nullptr_t, int, KEY> {
  inline void insert(const KEY& key) {
    this->update(key, nullptr);
  }

  using _Node = typename TreapSet::_Node;

  inline void _initRangeV(int& res) override {
    res = 0;
  }

  inline void _initV(_Node& node) override {
    node._rangeV = 0;
  }

  inline void _updateV(_Node& node, const nullptr_t& delta) override {
    _mergeRangeV(node);
  }

  inline void _mergeRangeV(_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + 1 +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

  inline void _appendNode(int& res, const _Node& node) override {
    ++res;
  }

  inline void _appendRange(int& res, const _Node& node) override {
    res += node._rangeV;
  }
};

} // namespace ds
