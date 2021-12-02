#pragma once

#include "ds/treap/base_lazy_treap.h"

namespace ds {

struct LazyTreapReverse : BaseLazyTreap<nullptr_t, bool, nullptr_t, int> {
  using NodeV = nullptr_t;
  using UpdateV = bool;
  using RangeV = nullptr_t;
  using Node = typename LazyTreapReverse::_Node;

  inline void _initRangeV(RangeV& rangeV) override {
    rangeV = 0;
  }

  inline void _initAllVs(Node& node, const NodeV& nodeV) override {
    node._updateV = false;
  }

  inline void _pushUpdate(UpdateV& updateV, const UpdateV& srcUpdateV) override {
    updateV ^= srcUpdateV;
  }

  inline void _appendNodeVWithUpdate(RangeV& rangeV, const Node& node) override {}

  inline void _appendRangeVWithUpdate(RangeV& rangeV, const Node& node) override {}

  inline void _mergeRangeV(_Node& node) override {}

  inline void _pushAndClearUpdate(_Node& node) override {
    if (node._updateV) {
      node._updateV = false;
      swap(node._lIdx, node._rIdx);
      if (node._lIdx >= 0) {
        _nodes[node._lIdx]._updateV ^= true;
      }
      if (node._rIdx >= 0) {
        _nodes[node._rIdx]._updateV ^= true;
      }
    }
  }
};

} // namespace ds
