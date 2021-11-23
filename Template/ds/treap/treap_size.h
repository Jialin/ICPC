#pragma once

#include "ds/treap/base_treap.h"

namespace ds {

template<typename KEY = int>
struct TreapSize : BaseTreap<bool, int, KEY> {
  inline void _initRangeV(int& res) override {
    res = 0;
  }

  inline void _initV(typename TreapSize::_Node& node) override {
    node._v = false;
    node._rangeV = 0;
  }

  inline void _updateV(typename TreapSize::_Node& node, const bool& delta) override {
    if (node._v ^ delta) {
      if (delta) {
        ++node._rangeV;
      } else {
        --node._rangeV;
      }
    }
    node._v = delta;
  }

  inline void _mergeRangeV(typename TreapSize::_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + node._v +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

  inline void _appendNode(int& res, const typename TreapSize::_Node& node) override {
    if (node._v) {
      ++res;
    }
  }

  inline void _appendRange(int& res, const typename TreapSize::_Node& node) override {
    res += node._rangeV;
  }
};

} // namespace ds
