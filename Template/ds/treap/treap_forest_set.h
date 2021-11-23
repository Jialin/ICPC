#pragma once

#include "ds/treap/base_treap_forest_macros.h"

#include "ds/treap/base_treap_macros.h"

#include "ds/treap/base_treap_forest.h"

namespace ds {

template<typename KEY = int>
struct TreapForestSet : BaseTreapForest<bool, int, KEY> {
  inline void insert(KEY key, int rootIdx) {
    this->update(key, true, rootIdx);
  }

  using _Node = typename BaseTreap<bool, int, KEY>::_Node;

  inline void _initRangeV(int& res) override {
    res = 0;
  }

  inline void _initV(_Node& node) override {
    node._v = false;
    node._rangeV = 0;
  }

  inline void _updateV(_Node& node, const bool& delta) override {
    if (node._v ^ delta) {
      if (delta) {
        ++node._rangeV;
      } else {
        --node._rangeV;
      }
    }
    node._v = delta;
  }

  inline void _mergeRangeV(_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + node._v +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

  inline void _appendNode(int& res, const _Node& node) override {
    if (node._v) {
      ++res;
    }
  }

  inline void _appendRange(int& res, const _Node& node) override {
    res += node._rangeV;
  }
};

} // namespace ds
