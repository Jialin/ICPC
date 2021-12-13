// !macro_gen
// ALL BASE_LAZY_TREAP_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<
    typename NODE_V,
    typename UPDATE_V = NODE_V,
    typename RANGE_V = UPDATE_V,
    typename KEY = int>
struct BaseLazyTreap {
  struct _Node {
    KEY _key;
    int _priority, _lIdx, _rIdx;
    NODE_V _v;
    UPDATE_V _updateV;
    RANGE_V _rangeV;
#ifdef _BASE_LAZY_TREAP_SIZE
    int _size;
#endif

    inline _Node(const KEY& key)
        : _key(key), _priority(rand()), _lIdx(-1), _rIdx(-1)
#ifdef _BASE_LAZY_TREAP_SIZE
          ,
          _size(1)
#endif
    {
    }
  };

  // Initializes range value
  virtual inline void _initRangeV(RANGE_V& rangeV) = 0;

  // Given <nodeV>, initializes all values for new node
  virtual inline void _initAllVs(_Node& node, const NODE_V& nodeV) = 0;

  // Pushes update to decendent node
  virtual inline void _pushUpdate(UPDATE_V& updateV, const UPDATE_V& srcUpdateV) = 0;

  // Pushes update value to decendent nodes and clear update
  virtual inline void _pushAndClearUpdate(_Node& node) = 0;

  // Merges range value from decendent nodes
  virtual inline void _mergeRangeV(_Node& node) = 0;

  inline BaseLazyTreap() {
    init();
  }

  inline void clear() {
    _roots.assign(_rootCnt, -1);
    _nodes.clear();
  }

  inline void init() {
    _rootCnt = 1;
    clear();
  }

#ifdef BASE_LAZY_TREAP_RESERVE_NODES // ^
  inline void reserveNodes(int n) {
    _nodes.reserve(n);
  }
#endif

#ifdef BASE_LAZY_TREAP_INIT_ORDERED_VALUES // ^

  // NOTE: if split is in use, DO NOT using batch init
  inline void initOrderedValues(const vector<NODE_V>& vs) {
    // BASE_LAZY_TREAP_INIT_ORDERED_VALUES => _BASE_LAZY_TREAP_INIT_ORDERED_VALUES
    _roots[0] = _initOrderedValues(vs, 0, SIZE(vs));
  }
#endif

#ifdef _BASE_LAZY_TREAP_INIT_ORDERED_VALUES // ^
  inline int _initOrderedValues(const vector<NODE_V>& vs, int lower, int upper) {
    if (lower >= upper) {
      return -1;
    }
    int medium = (lower + upper) >> 1;
    // _BASE_LAZY_TREAP_INIT_ORDERED_VALUES => _BASE_LAZY_TREAP_NEW_NODE
    int newIdx = _newNode(medium, vs[medium]);
    int lIdx = _initOrderedValues(vs, lower, medium);
    int rIdx = _initOrderedValues(vs, medium + 1, upper);
    _nodes[newIdx]._lIdx = lIdx;
    _nodes[newIdx]._rIdx = rIdx;
    // _BASE_LAZY_TREAP_INIT_ORDERED_VALUES => _BASE_LAZY_TREAP_HEAPIFY
    return _heapify(newIdx);
  }
#endif

#ifdef BASE_LAZY_TREAP_PUSH_ALL // ^
  inline void pushAll() {
    // BASE_LAZY_TREAP_PUSH_ALL => _BASE_LAZY_TREAP_PUSH_ALL
    _pushAll(_roots[0]);
  }
#endif

#ifdef _BASE_LAZY_TREAP_PUSH_ALL // ^
  inline void _pushAll(int idx) {
    if (idx < 0) {
      return;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    _pushAll(node._lIdx);
    _pushAll(node._rIdx);
    // _BASE_LAZY_TREAP_PUSH_ALL => _BASE_LAZY_TREAP_MERGE_V
    _mergeV(node);
  }
#endif

#ifdef BASE_LAZY_TREAP_INSERT_LEFTMOST // ^
  inline void insertLeftmost(const KEY& key, const NODE_V& v) {
    // BASE_LAZY_TREAP_INSERT_LEFTMOST => _BASE_LAZY_TREAP_INSERT_LEFTMOST
    _roots[0] = _insertLeftmost(_roots[0], key, v);
  }
#endif

#ifdef _BASE_LAZY_TREAP_INSERT_LEFTMOST // ^
  inline int _insertLeftmost(int idx, const KEY& key, const NODE_V& v) {
    if (idx < 0) {
      // _BASE_LAZY_TREAP_INSERT_LEFTMOST => _BASE_LAZY_TREAP_NEW_NODE
      return _newNode(key, v);
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    _nodes[idx]._lIdx = _insertLeftmost(node._lIdx, key, v);
    // _BASE_LAZY_TREAP_INSERT_LEFTMOST => _BASE_LAZY_TREAP_HEAPIFY
    return _heapify(idx);
  }
#endif

#ifdef _BASE_LAZY_TREAP_INSERT_NODE_LEFTMOST // ^
  inline int _insertNodeLeftmost(int idx, int insertIdx) {
    if (idx < 0) {
      return insertIdx;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    int lIdx = _insertNodeLeftmost(node._lIdx, insertIdx);
    _nodes[idx]._lIdx = lIdx;
    // _BASE_LAZY_TREAP_INSERT_NODE_LEFTMOST => _BASE_LAZY_TREAP_HEAPIFY
    return _heapify(idx);
  }
#endif

#ifdef BASE_LAZY_TREAP_INSERT_RIGHTMOST // ^
  inline void insertRightmost(const KEY& key, const NODE_V& v) {
    // BASE_LAZY_TREAP_INSERT_RIGHTMOST => _BASE_LAZY_TREAP_INSERT_RIGHTMOST
    _roots[0] = _insertRightmost(_roots[0], key, v);
  }
#endif

#ifdef _BASE_LAZY_TREAP_INSERT_RIGHTMOST // ^
  inline int _insertRightmost(int idx, const KEY& key, const NODE_V& v) {
    if (idx < 0) {
      // _BASE_LAZY_TREAP_INSERT_RIGHTMOST => _BASE_LAZY_TREAP_NEW_NODE
      return _newNode(key, v);
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    int rIdx = _insertRightmost(node._rIdx, key, v);
    _nodes[idx]._rIdx = rIdx;
    // _BASE_LAZY_TREAP_INSERT_RIGHTMOST => _BASE_LAZY_TREAP_HEAPIFY
    return _heapify(idx);
  }
#endif

#ifdef BASE_LAZY_TREAP_ERASE_LEFTMOST // ^
  inline _Node* eraseLeftmost() {
    // BASE_LAZY_TREAP_ERASE_LEFTMOST => _BASE_LAZY_TREAP_ERASE_LEFTMOST
    return _eraseLeftmost(_roots[0]);
  }
#endif

#ifdef _BASE_LAZY_TREAP_ERASE_LEFTMOST // ^
  inline _Node* _eraseLeftmost(int& idx) {
    if (idx < 0) {
      return nullptr;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    if (node._lIdx < 0) {
      idx = node._rIdx;
      node._rIdx = -1;
      // _BASE_LAZY_TREAP_ERASE_LEFTMOST => _BASE_LAZY_TREAP_MERGE_V
      _mergeV(node);
      return &node;
    }
    auto* res = _eraseLeftmost(node._lIdx);
    _mergeV(node);
    return res;
  }
#endif

#ifdef BASE_LAZY_TREAP_ERASE_RIGHTMOST // ^
  inline _Node* eraseRightmost() {
    // BASE_LAZY_TREAP_ERASE_RIGHTMOST => _BASE_LAZY_TREAP_ERASE_RIGHTMOST
    return _eraseRightmost(_roots[0]);
  }
#endif

#ifdef _BASE_LAZY_TREAP_ERASE_RIGHTMOST // ^
  inline _Node* _eraseRightmost(int& idx) {
    if (idx < 0) {
      return nullptr;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    if (node._rIdx < 0) {
      idx = node._lIdx;
      node._lIdx = -1;
      // _BASE_LAZY_TREAP_ERASE_RIGHTMOST => _BASE_LAZY_TREAP_MERGE_V
      _mergeV(node);
      return &node;
    }
    auto* res = _eraseRightmost(node._rIdx);
    _mergeV(node);
    return res;
  }
#endif

#ifdef _BASE_LAZY_TREAP_NEW_NODE // ^
  inline int _newNode(const KEY& key, const NODE_V& v) {
    int idx = SIZE(_nodes);
    _nodes.emplace_back(key);
    _initAllVs(_nodes.back(), v);
    return idx;
  }
#endif

#ifdef _BASE_LAZY_TREAP_HEAPIFY // ^
  inline int _heapify(int idx) {
    if (idx < 0) {
      return -1;
    }
    auto& node = _nodes[idx];
    int lIdx = node._lIdx;
    int rIdx = node._rIdx;
    if (lIdx >= 0 && _nodes[lIdx]._priority > node._priority &&
        (rIdx < 0 || _nodes[lIdx]._priority > _nodes[rIdx]._priority)) {
      auto& lNode = _nodes[lIdx];
      node._lIdx = lNode._rIdx;
      lNode._rIdx = _heapify(idx);
      // _BASE_TREAP_HEAPIFY => _BASE_LAZY_TREAP_MERGE_V
      _mergeV(lNode);
      return lIdx;
    }
    if (rIdx >= 0 && _nodes[rIdx]._priority > node._priority &&
        (lIdx < 0 || _nodes[rIdx]._priority > _nodes[lIdx]._priority)) {
      auto& rNode = _nodes[rIdx];
      node._rIdx = rNode._lIdx;
      rNode._lIdx = _heapify(idx);
      _mergeV(rNode);
      return rIdx;
    }
    _mergeV(node);
    return idx;
  }
#endif

#ifdef BASE_LAZY_TREAP_CALC_LEFTMOST // ^
  inline const _Node* calcLeftmost() {
    // BASE_LAZY_TREAP_CALC_LEFTMOST => _BASE_LAZY_TREAP_CALC_LEFTMOST
    return _calcLeftmost(_roots[0]);
  }
#endif

#ifdef _BASE_LAZY_TREAP_CALC_LEFTMOST // ^
  inline const _Node* _calcLeftmost(int idx) {
    if (idx < 0) {
      return nullptr;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    if (node._lIdx >= 0) {
      const auto* res = _calcLeftmost(node._lIdx);
      // _BASE_LAZY_TREAP_CALC_LEFTMOST => _BASE_LAZY_TREAP_MERGE_V
      _mergeV(node);
      return res;
    } else {
      _mergeV(node);
      return &node;
    }
  }
#endif

#ifdef BASE_LAZY_TREAP_CALC_RIGHTMOST // ^
  inline const _Node* calcRightmost() {
    // BASE_LAZY_TREAP_CALC_RIGHTMOST => _BASE_LAZY_TREAP_CALC_RIGHTMOST
    return _calcRightmost(_roots[0]);
  }
#endif

#ifdef _BASE_LAZY_TREAP_CALC_RIGHTMOST // ^
  inline const _Node* _calcRightmost(int idx) {
    if (idx < 0) {
      return nullptr;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    if (node._rIdx >= 0) {
      const auto* res = _calcRightmost(node._rIdx);
      // _BASE_LAZY_TREAP_CALC_RIGHTMOST => _BASE_LAZY_TREAP_MERGE_V
      _mergeV(node);
      return res;
    } else {
      _mergeV(node);
      return &node;
    }
  }
#endif

#ifdef BASE_LAZY_TREAP_CALC_KTH // ^
  inline const _Node* calcKth(int kth) {
    // BASE_LAZY_TREAP_CALC_KTH => _BASE_LAZY_TREAP_CALC_KTH
    return _calcKth(_roots[0], kth);
  }
#endif

#ifdef _BASE_LAZY_TREAP_CALC_KTH // ^
  inline const _Node* _calcKth(int idx, int kth) {
    if (idx < 0) {
      return nullptr;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    // _BASE_LAZY_TREAP_CALC_KTH => _BASE_LAZY_TREAP_MERGE_V
    _mergeV(node);
    int lSize = _calcSize(node._lIdx);
    if (kth < lSize) {
      return _calcKth(node._lIdx, kth);
    } else {
      kth -= lSize;
      if (kth) {
        return _calcKth(node._rIdx, kth - 1);
      } else {
        return &node;
      }
    }
  }
#endif

#ifdef BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH // ^
  inline void cyclicRotateRightByKth(int lower, int upper) {
    // BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH => _BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH
    _roots[0] = _rotateCyclicRightByKth(_roots[0], lower, upper);
  }
#endif

#ifdef _BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH // ^
  inline int _rotateCyclicRightByKth(int idx, int lower, int upper) {
    if (idx < 0 || upper - lower <= 1) {
      return idx;
    }
    int lIdx, mIdx, rIdx;
    // _BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH => _BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH
    _splitRangeByKth(idx, lower, upper, lIdx, mIdx, rIdx);
    if (mIdx >= 0) {
      // _BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH => _BASE_LAZY_TREAP_ERASE_RIGHTMOST
      auto* node = _eraseRightmost(mIdx);
      _initAllVs(*node, node->_v);
      node->_lIdx = -1;
#ifdef _BASE_LAZY_TREAP_SIZE
      node->_size = 1;
#endif
      // _BASE_LAZY_TREAP_CYCLIC_ROTATE_RIGHT_BY_KTH => _BASE_LAZY_TREAP_INSERT_NODE_LEFTMOST
      mIdx = _insertNodeLeftmost(mIdx, node - _nodes.data());
    }
    // _BASE_LAZY_TREAP_ROTATE_RIGHT_BY_KTH => _BASE_LAZY_TREAP_MERGE3
    return _merge3(lIdx, mIdx, rIdx);
  }
#endif

#ifdef BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH // ^
  inline void updateRangeByKth(int lower, int upper, const UPDATE_V& updateV) {
    // BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH => _BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH
    _roots[0] = _updateRangeByKth(_roots[0], lower, upper, updateV);
  }
#endif

#ifdef _BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH // ^
  inline int _updateRangeByKth(int idx, int lower, int upper, const UPDATE_V& updateV) {
    if (idx < 0) {
      return -1;
    }
    int lIdx, mIdx, rIdx;
    // _BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH => _BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH
    _splitRangeByKth(idx, lower, upper, lIdx, mIdx, rIdx);
    if (mIdx >= 0) {
      _pushUpdate(_nodes[mIdx]._updateV, updateV);
    }
    // _BASE_LAZY_TREAP_UPDATE_RANGE_BY_KTH => _BASE_LAZY_TREAP_MERGE3
    return _merge3(lIdx, mIdx, rIdx);
  }
#endif

#ifdef _BASE_LAZY_TREAP_SPLIT // ^
  inline void _split(int idx, const KEY& bound, int& lIdx, int& rIdx) {
    if (idx < 0) {
      lIdx = -1;
      rIdx = -1;
      return;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    if (bound < node._key) {
      _split(node._lIdx, bound, lIdx, node._lIdx);
      rIdx = idx;
    } else if (bound == node._key) {
      lIdx = node._lIdx;
      node._lIdx = -1;
      rIdx = idx;
    } else {
      _split(node._rIdx, bound, node._rIdx, rIdx);
      lIdx = idx;
    }
    // _BASE_LAZY_TREAP_SPLIT => _BASE_LAZY_TREAP_MERGE_V
    _mergeV(node);
  }
#endif

#ifdef _BASE_LAZY_TREAP_INSERT_NODE // ^
  inline int _insertNode(int idx, int insertIdx) {
    if (idx < 0) {
      return insertIdx;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    auto& iNode = _nodes[insertIdx];
    if (iNode._key < node._key) {
      _nodes[idx]._lIdx = _insertNode(node._lIdx, insertIdx);
    } else if (node._key == iNode._key) {
      _initAllVs(node, iNode._v);
    } else {
      _nodes[idx]._rIdx = _insertNode(node._rIdx, insertIdx);
    }
    // BASE_LAZY_TREAP_INSERT => _BASE_LAZY_TREAP_HEAPIFY
    return _heapify(idx);
  }
#endif

#ifdef _BASE_LAZY_TREAP_SPLIT_BY_KTH // ^
  inline void _splitByKth(int idx, int kth, int& lIdx, int& rIdx) {
#ifdef LOCAL
    DEBUG_GE(kth, 0);
#endif
    if (idx < 0 || !kth) {
      lIdx = -1;
      rIdx = idx;
      return;
    }
    if (_calcSize(idx) <= kth) {
      lIdx = idx;
      rIdx = -1;
      return;
    }
    auto& node = _nodes[idx];
    _pushAndClearUpdate(node);
    // _BASE_LAZY_TREAP_SPLIT_BY_KTH => _BASE_LAZY_TREAP_SIZE
    if (kth <= _calcSize(node._lIdx)) {
      _splitByKth(node._lIdx, kth, lIdx, node._lIdx);
      rIdx = idx;
    } else {
      _splitByKth(node._rIdx, kth - _calcSize(node._lIdx) - 1, node._rIdx, rIdx);
      lIdx = idx;
    }
    _mergeV(node);
  }
#endif

#ifdef BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH // ^
  inline void splitRangeByKth(int lower, int upper, int& lIdx, int& mIdx, int& rIdx) {
    // BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH => _BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH
    _splitRangeByKth(_roots[0], lower, upper, lIdx, mIdx, rIdx);
  }
#endif

#ifdef _BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH // ^
  inline void _splitRangeByKth(int idx, int lower, int upper, int& lIdx, int& mIdx, int& rIdx) {
    // _BASE_LAZY_TREAP_SPLIT_RANGE_BY_KTH => _BASE_LAZY_TREAP_SPLIT_BY_KTH
    _splitByKth(idx, upper, mIdx, rIdx);
    _splitByKth(mIdx, lower, lIdx, mIdx);
  }
#endif

#ifdef BASE_LAZY_TREAP_MERGE3 // ^
  inline void merge3(int lIdx, int mIdx, int rIdx) {
    // BASE_LAZY_TREAP_MERGE3 => _BASE_LAZY_TREAP_MERGE3
    _roots[0] = _merge3(lIdx, mIdx, rIdx);
  }
#endif

#ifdef _BASE_LAZY_TREAP_MERGE3 // ^
  inline int _merge3(int lIdx, int mIdx, int rIdx) {
    // _BASE_LAZY_TREAP_MERGE3 => _BASE_LAZY_TREAP_MERGE
    return _merge(_merge(lIdx, mIdx), rIdx);
  }
#endif

#ifdef _BASE_LAZY_TREAP_MERGE // ^
  inline int _merge(int lIdx, int rIdx) {
    if (lIdx < 0) {
      return rIdx;
    }
    if (rIdx < 0) {
      return lIdx;
    }
    auto& lNode = _nodes[lIdx];
    _pushAndClearUpdate(lNode);
    auto& rNode = _nodes[rIdx];
    _pushAndClearUpdate(rNode);
    if (lNode._priority > rNode._priority) {
      lNode._rIdx = _merge(lNode._rIdx, rIdx);
      // _BASE_LAZY_TREAP_MERGE => _BASE_LAZY_TREAP_MERGE_V
      _mergeV(lNode);
      return lIdx;
    } else {
      rNode._lIdx = _merge(lIdx, rNode._lIdx);
      _mergeV(rNode);
      return rIdx;
    }
  }
#endif

#ifdef _BASE_LAZY_TREAP_MERGE_V // ^
  inline void _mergeV(_Node& node) {
    _mergeRangeV(node);
#ifdef _BASE_LAZY_TREAP_SIZE
    node._size = _calcSize(node._lIdx) + 1 + _calcSize(node._rIdx);
#endif
  }
#endif

#ifdef _BASE_LAZY_TREAP_SIZE // ^
  inline int _calcSize(int idx) {
    return idx >= 0 ? _nodes[idx]._size : 0;
  }
#endif

  vector<_Node> _nodes;
  vector<int> _roots;
  int _rootCnt;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const _Node& node) {
    o << "[key:" << node._key << "] (v:" << tostring(node._v)
      << " updateV:" << tostring(node._updateV) << " rangeV:" << tostring(node._rangeV);
#ifdef _BASE_LAZY_TREAP_SIZE
    o << " size:" << node._size;
#endif
    o << " priority:" << node._priority << ")";
    return o;
  }

  inline friend ostream& operator<<(ostream& o, const BaseLazyTreap& treap) {
    o << "total root cnt:" << treap._roots.size();
    for (int root : treap._roots) {
      treap._output(0, root, o);
    }
    return o;
  }

  inline void _output(int depth, int idx, ostream& o) const {
    o << endl << string(depth, '\t');
    if (idx < 0) {
      o << '-';
      return;
    }
    const auto& node = _nodes[idx];
    o << node << " @" << idx;
    if (node._lIdx >= 0 || node._rIdx >= 0) {
      _output(depth + 1, node._lIdx, o);
      _output(depth + 1, node._rIdx, o);
    }
  }
#endif
};

} // namespace ds
