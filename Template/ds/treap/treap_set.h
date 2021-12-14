// !macro_gen
// ALL TREAP_SET_ALL
#pragma once

#include "ds/treap/base_treap_macros.h" // INCLUDE

#include "ds/treap/base_treap.h"

namespace ds {

template<typename KEY = int>
struct TreapSet : BaseTreap<nullptr_t, nullptr_t, KEY> {
#ifdef TREAP_SET_INSERT // ^
  inline void insert(const KEY& key) {
    // TREAP_SET_INSERT => BASE_TREAP_UPDATE
    this->update(key, nullptr);
  }
#endif

  using NodeV = nullptr_t;
  using RangeV = nullptr_t;
  using Node = typename TreapSet::_Node;

  inline void _initRangeV(RangeV& res) override {}

  inline void _initAllVs(Node& node, const NodeV& nodeV) override {}

  inline void _updateAllVs(Node& node, const NodeV& delta) override {}

  inline void _mergeRangeV(Node& node) override {}

#ifdef _BASE_TREAP_CALC_APPEND
  inline void _appendNode(RangeV& res, const Node& node) override {}

  inline void _appendRange(RangeV& res, const Node& node) override {}
#endif
};

} // namespace ds
