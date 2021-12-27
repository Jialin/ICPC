#pragma once

#include "common/macros.h"
#include "ds/segment_tree/base_lazy_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_segment_tree.h"

namespace ds {

template<typename _V, typename _InitV = _V, typename _Update = _InitV>
struct LazySegmentTreeUpdateMin : BaseLazySegmentTree<_V, _InitV, _Update> {
  using V = _V;
  using InitV = _InitV;
  using Update = _Update;
  using Node = typename LazySegmentTreeUpdateMin::Node;

#ifdef _BASE_LAZY_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = numeric_limits<V>::max();
  }
#endif

#ifdef _BASE_LAZY_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    MMIN(res, node.v);
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.v += update;
    node.update += update;
  }

  inline void _clearUpdate(Node& node) override {
    node.update = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = min(lNode.v, rNode.v);
  }
};

} // namespace ds
