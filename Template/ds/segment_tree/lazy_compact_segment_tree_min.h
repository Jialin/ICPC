#pragma once

#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "common/macros.h"
#include "ds/segment_tree/base_lazy_compact_segment_tree.h"

namespace ds {

template<typename V, typename InitV = V, typename Update = InitV>
struct LazyCompactSegmentTreeMin : BaseLazyCompactSegmentTree<
                                       V,
                                       InitV,
                                       Update
#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
                                       ,
                                       nullptr_t
#endif
                                       > {
#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  using TraverseArgs = nullptr_t;
#endif
  using Node = typename LazyCompactSegmentTreeMin::_Node;

  inline V getMin(const Node& node) {
    return node.v + node.update;
  }

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  inline typename LazyCompactSegmentTreeMin::Traverse
  _traverse(Node& node, int lower, int upper, TraverseArgs& args) override {
    return LazyCompactSegmentTreeMin::Traverse::NONE;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = numeric_limits<V>::max();
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    MMIN(res, getMin(node));
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    node.update += update;
  }

  inline void _clearUpdate(Node& node) override {
    node.update = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = min(getMin(lNode), getMin(rNode));
  }
};

} // namespace ds
