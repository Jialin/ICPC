#pragma once

#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"

namespace ds {

template<typename _V, typename _InitV = _V, typename _Update = pair<int, _V>>
struct LazyCompactSegmentTreeUpdateSetSum : BaseLazyCompactSegmentTree<_V, _InitV, _Update> {
  using V = int64_t;
  using InitV = int;
  using Update = pair<int, int64_t>;
  using Node = typename LazyCompactSegmentTreeUpdateSetSum::Node;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res = 0;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    res += node.v;
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update.first;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    int64_t delta = update.second * (node.upper - node.lower);
    if (update.first == 2) {
      node.update.first = 2;
      node.update.second = update.second;
      node.v = delta;
    } else {
      assert(update.first == 1);
      node.update.first = node.update.first < 2 ? 1 : 2;
      node.update.second += update.second;
      node.v += delta;
    }
  }

  inline void _clearUpdate(Node& node) override {
    node.update.first = 0;
    node.update.second = 0;
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    res = lNode.v + rNode.v;
  }

  inline void changeRange(int lower, int upper, V delta) {
    this->updateRange(lower, upper, {1, move(delta)});
  }

  inline void setRange(int lower, int upper, V v) {
    this->updateRange(lower, upper, {2, move(v)});
  }
};

} // namespace ds
