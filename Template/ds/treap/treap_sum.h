#pragma once

#include "ds/treap/base_treap.h"

namespace ds {

template<typename V, typename KEY = int>
struct TreapSum : BaseTreap<V, V, KEY> {
  using _Node = typename TreapSum::_Node;

  inline void _initRangeV(V& res) override {
    res = 0;
  }

  inline void _initV(_Node& node) override {
    node._v = node._rangeV = 0;
  }

  inline void _updateV(_Node& node, const V& delta) override {
    node._v += delta;
    node._rangeV += delta;
  }

  inline void _mergeRangeV(_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + node._v +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

  inline void _appendNode(V& res, const _Node& node) override {
    res += node._v;
  }

  inline void _appendRange(V& res, const _Node& node) override {
    res += node._rangeV;
  }
};

} // namespace ds
