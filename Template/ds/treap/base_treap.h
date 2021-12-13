// !macro_gen
// ALL BASE_TREAP_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename NODE_V, typename RANGE_V = NODE_V, typename KEY = int>
struct BaseTreap {
  struct _Node {
    KEY _key;
    int _priority, _lIdx, _rIdx;
    NODE_V _v;
    RANGE_V _rangeV;
#ifdef _BASE_TREAP_SIZE
    int _size;
#endif

    inline _Node(const KEY& key)
        : _key(key), _priority(rand()), _lIdx(-1), _rIdx(-1)
#ifdef _BASE_TREAP_SIZE
          ,
          _size(1)
#endif
    {
    }

// TODO: get rid of, update the priority in initAllVs
#ifdef _BASE_TREAP_NEW_NODE_WITH_PRIORITY
    inline _Node(const KEY& key, int priority)
        : _key(key), _priority(priority), _lIdx(-1), _rIdx(-1) {}
#endif
  };

  // Initializes range value
  virtual inline void _initRangeV(RANGE_V& res) = 0;

  // Given <nodeV>, initializes all values for new node
  virtual inline void _initAllVs(_Node& node, const NODE_V& nodeV) = 0;

  // Given delta, updates all values of the node
  virtual inline void _updateAllVs(_Node& node, const NODE_V& delta) = 0;

  // Merges the range value of the node from descendent nodes
  virtual inline void _mergeRangeV(_Node& node) = 0;

#ifdef _BASE_TREAP_CALC_APPEND
  // Appends the node value to the result
  virtual inline void _appendNode(RANGE_V& res, const _Node& idx) = 0;

  // Appends the range value to the result
  virtual inline void _appendRange(RANGE_V& res, const _Node& idx) = 0;
#endif

  inline BaseTreap() {
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

#ifdef BASE_TREAP_RESERVE_NODES // ^
  inline void reserveNodes(int n) {
    _nodes.reserve(n);
  }
#endif

#ifdef BASE_TREAP_INIT_ORDERED_ITEMS // ^
  inline void initOrderedItems(const vector<pair<KEY, NODE_V>>& items) {
    // BASE_TREAP_INIT_ORDERED_ITEMS => _BASE_TREAP_INIT_ORDERED_ITEMS
    _roots[0] = _initOrderedItems(items, 0, SIZE(items));
  }
#endif

#ifdef _BASE_TREAP_INIT_ORDERED_ITEMS // ^
  inline int _initOrderedItems(const vector<pair<KEY, NODE_V>>& items, int lower, int upper) {
    if (lower >= upper) {
      return -1;
    }
    int medium = (lower + upper) >> 1;
    // _BASE_TREAP_INIT_ORDERED_ITEMS => _BASE_TREAP_NEW_NODE
    int newIdx = _newNode(items[medium].first, items[medium].second);
    int lIdx = _initOrderedItems(items, lower, medium);
    int rIdx = _initOrderedItems(items, medium + 1, upper);
    _nodes[newIdx]._lIdx = lIdx;
    _nodes[newIdx]._rIdx = rIdx;
    // _BASE_TREAP_INIT_ORDERED_ITEMS => _BASE_TREAP_HEAPIFY
    return _heapify(newIdx);
  }
#endif

#ifdef BASE_TREAP_INIT_ORDERED_ITEMS_WITH_PRIORITY // ^
  inline void initOrderedItemsWithPriority(const vector<tuple<KEY, int, NODE_V>>& items) {
    // BASE_TREAP_INIT_ORDERED_ITEMS_WITH_PRIORITY => _BASE_TREAP_INIT_ORDERED_ITEMS_WITH_PRIORITY
    _roots[0] = _initOrderedItemsWithPriority(items, 0, SIZE(items));
  }
#endif

#ifdef _BASE_TREAP_INIT_ORDERED_ITEMS_WITH_PRIORITY // ^
  inline int
  _initOrderedItemsWithPriority(const vector<tuple<KEY, int, NODE_V>>& items, int from, int to) {
    if (from >= to) {
      return -1;
    }
    int medium = (from + to) >> 1;
    // _BASE_TREAP_INIT_ORDERED_ITEMS_WITH_PRIORITY => _BASE_TREAP_NEW_NODE_WITH_PRIORITY
    int newIdx =
        _newNodeWithPriority(get<0>(items[medium]), get<1>(items[medium]), get<2>(items[medium]));
    _nodes[newIdx]._lIdx = _initOrderedItemsWithPriority(items, from, medium);
    _nodes[newIdx]._rIdx = _initOrderedItemsWithPriority(items, medium + 1, to);
    // _BASE_TREAP_INIT_ORDERED_ITEMS_WITH_PRIORITY => _BASE_TREAP_HEAPIFY
    return _heapify(newIdx);
  }
#endif

#ifdef _BASE_TREAP_HEAPIFY // ^
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
      // _BASE_TREAP_HEAPIFY => _BASE_TREAP_MERGE_V
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

#ifdef BASE_TREAP_INIT_ORDERED_VALUES // ^
  inline void initOrderedValues(const vector<NODE_V>& vs) {
    // BASE_TREAP_INIT_ORDERED_VALUES => _BASE_TREAP_INIT_ORDERED_VALUES
    _roots[0] = _initOrderedValues(vs, 0, SIZE(vs));
  }
#endif

#ifdef _BASE_TREAP_INIT_ORDERED_VALUES // ^
  inline int _initOrderedValues(const vector<NODE_V>& vs, int from, int to) {
    if (from >= to) {
      return -1;
    }
    int medium = (from + to) >> 1;
    // _BASE_TREAP_INIT_ORDERED_VALUES => _BASE_TREAP_NEW_NODE
    int newIdx = _newNode(medium, vs[medium]);
    _nodes[newIdx]._lIdx = _initOrderedValues(vs, from, medium);
    _nodes[newIdx]._rIdx = _initOrderedValues(vs, medium + 1, to);
    // _BASE_TREAP_INIT_ORDERED_VALUES => _BASE_TREAP_HEAPIFY
    return _heapify(newIdx);
  }
#endif

#ifdef _BASE_TREAP_NEW_NODE // ^
  inline int _newNode(const KEY& key, const NODE_V& v) {
    int idx = SIZE(_nodes);
    _nodes.emplace_back(key);
    auto& node = _nodes.back();
    _initAllVs(node, v);
    return idx;
  }
#endif

#ifdef _BASE_TREAP_NEW_NODE_WITH_PRIORITY // ^
  inline int _newNodeWithPriority(const KEY& key, int priority, const NODE_V& v) {
    int idx = SIZE(_nodes);
    _nodes.emplace_back(key, priority);
    auto& node = _nodes.back();
    _initAllVs(node, v);
    return idx;
  }
#endif

#ifdef BASE_TREAP_UPDATE // ^
  inline void update(const KEY& key, const NODE_V& delta) {
    // BASE_TREAP_UPDATE => _BASE_TREAP_UPDATE
    _roots[0] = _update(_roots[0], key, delta);
  }
#endif

#ifdef _BASE_TREAP_UPDATE // ^
  // Returns the new root index
  inline int _update(int idx, const KEY& key, const NODE_V& delta) {
    if (idx < 0) {
      // _BASE_TREAP_UPDATE => _BASE_TREAP_NEW_NODE
      return _newNode(key, delta);
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      _updateAllVs(node, delta);
      return idx;
    }
    if (key < node._key) {
      int newIdx = _update(node._lIdx, key, delta);
      // _update might invalidate the vector reference
      auto& node2 = _nodes[idx];
      node2._lIdx = newIdx;
      if (_nodes[newIdx]._priority > node2._priority) {
        // _BASE_TREAP_UPDATE => _BASE_TREAP_ROTATE
        _rotateLeft(idx, newIdx);
        return newIdx;
      }
    } else {
      int newIdx = _update(node._rIdx, key, delta);
      // _update might invalidate the vector reference
      auto& node2 = _nodes[idx];
      node2._rIdx = newIdx;
      if (_nodes[newIdx]._priority > node2._priority) {
        _rotateRight(idx, node2._rIdx);
        return newIdx;
      }
    }
    // _BASE_TREAP_UPDATE => _BASE_TREAP_MERGE_V
    _mergeV(_nodes[idx]);
    return idx;
  }
#endif

#ifdef _BASE_TREAP_ROTATE // ^
  inline void _rotateLeft(int idx, int lIdx) {
    auto& node = _nodes[idx];
    auto& lNode = _nodes[lIdx];
    node._lIdx = lNode._rIdx;
    lNode._rIdx = idx;
    // _BASE_TREAP_ROTATE => _BASE_TREAP_MERGE_V
    _mergeV(node);
    _mergeV(lNode);
  }

  inline void _rotateRight(int idx, int rIdx) {
    auto& node = _nodes[idx];
    auto& rNode = _nodes[rIdx];
    node._rIdx = rNode._lIdx;
    rNode._lIdx = idx;
    // _BASE_TREAP_ROTATE => _BASE_TREAP_MERGE_V
    _mergeV(node);
    _mergeV(rNode);
  }
#endif

#ifdef BASE_TREAP_ERASE // ^
  inline void erase(const KEY& key) {
    // BASE_TREAP_ERASE => _BASE_TREAP_ERASE
    _roots[0] = _erase(_roots[0], key);
  }
#endif

#ifdef _BASE_TREAP_ERASE // ^
  inline int _erase(int idx, const KEY& key) {
    if (idx < 0) {
      return -1;
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      // _BASE_TREAP_ERASE => _BASE_TREAP_MERGE
      return _merge(node._lIdx, node._rIdx);
    }
    if (key < node._key) {
      node._lIdx = _erase(node._lIdx, key);
    } else {
      node._rIdx = _erase(node._rIdx, key);
    }
    // _BASE_TREAP_ERASE => _BASE_TREAP_MERGE_V
    _mergeV(node);
    return idx;
  }
#endif

#ifdef _BASE_TREAP_MERGE // ^
  inline int _merge(int lIdx, int rIdx) {
    if (lIdx < 0) {
      return rIdx;
    }
    if (rIdx < 0) {
      return lIdx;
    }
    auto& lNode = _nodes[lIdx];
    auto& rNode = _nodes[rIdx];
    if (lNode._priority > rNode._priority) {
      lNode._rIdx = _merge(lNode._rIdx, rIdx);
      // _BASE_TREAP_MERGE => _BASE_TREAP_MERGE_V
      _mergeV(lNode);
      return lIdx;
    } else {
      rNode._lIdx = _merge(lIdx, rNode._lIdx);
      _mergeV(rNode);
      return rIdx;
    }
  }
#endif

#ifdef BASE_TREAP_LOWER_BOUND_BOUNDED // ^
  // Finds the first node whose range value from <lower> is NOT less than <rangeV>
  inline const _Node* lowerBoundBounded(const KEY& lower, const RANGE_V& rangeV) {
    // _BASE_TREAP_LOWER_BOUND_BOUNDED => _BASE_TREAP_TMP_RANGE_V
    _initRangeV(_tmpRangeV);
    // BASE_TREAP_LOWER_BOUND_BOUNDED => _BASE_TREAP_LOWER_BOUND_BOUNDED
    return _lowerBoundBounded(_roots[0], lower, rangeV, _tmpRangeV);
  }
#endif

#ifdef _BASE_TREAP_LOWER_BOUND_BOUNDED // ^
  inline const _Node*
  _lowerBoundBounded(int& idx, const KEY& lower, const RANGE_V& rangeV, RANGE_V& curRangeV) {
    int lIdx, rIdx;
    // _BASE_TREAP_LOWER_BOUND_BOUNDED => _BASE_TREAP_SPLIT
    _split(idx, lower, lIdx, rIdx);
    // _BASE_TREAP_LOWER_BOUND_BOUNDED => _BASE_TREAP_LOWER_BOUND
    const auto* res = _lowerBound(rIdx, rangeV, curRangeV);
    // _BASE_TREAP_LOWER_BOUND_BOUNDED => _BASE_TREAP_MERGE
    idx = _merge(lIdx, rIdx);
    return res;
  }
#endif

#ifdef _BASE_TREAP_LOWER_BOUND // ^
  inline const _Node* _lowerBound(int idx, const RANGE_V& rangeV, RANGE_V& curRangeV) {
    if (idx < 0) {
      return nullptr;
    }
    const auto& node = _nodes[idx];
    if (node._lIdx >= 0) {
      DEBUG_NE(&curRangeV, &_tmpRangeV2);
      // _BASE_TREAP_LOWER_BOUND => _BASE_TREAP_TMP_RANGE_V2
      _tmpRangeV2 = curRangeV;
      _appendRange(curRangeV, _nodes[node._lIdx]);
      if (!(curRangeV < rangeV)) {
        swap(curRangeV, _tmpRangeV2);
        return _lowerBound(node._lIdx, rangeV, curRangeV);
      }
    }
    _appendNode(curRangeV, node);
    if (!(curRangeV < rangeV)) {
      return &node;
    }
    if (node._rIdx >= 0) {
      DEBUG_NE(&curRangeV, &_tmpRangeV2);
      // _BASE_TREAP_LOWER_BOUND => _BASE_TREAP_TMP_RANGE_V2
      _tmpRangeV2 = curRangeV;
      _appendRange(curRangeV, _nodes[node._rIdx]);
      if (!(curRangeV < rangeV)) {
        swap(curRangeV, _tmpRangeV2);
        return _lowerBound(node._rIdx, rangeV, curRangeV);
      }
    }
    return nullptr;
  }
#endif

#ifdef BASE_TREAP_CALC_PREFIX // ^
  inline RANGE_V calcPrefix(const KEY& upper) {
    RANGE_V res;
    _initRangeV(res);
    // BASE_TREAP_CALC_PREFIX => _BASE_TREAP_CALC_PREFIX
    _calcPrefix(_roots[0], upper, res);
    return res;
  }
#endif

#ifdef _BASE_TREAP_CALC_PREFIX // ^
  inline void _calcPrefix(int idx, const KEY& upper, RANGE_V& res) {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    if (node._key < upper) {
      // _BASE_TREAP_CALC_PREFIX => _BASE_TREAP_CALC_APPEND
      if (node._lIdx >= 0) {
        _appendRange(res, _nodes[node._lIdx]);
      }
      _appendNode(res, node);
      _calcPrefix(node._rIdx, upper, res);
    } else {
      _calcPrefix(node._lIdx, upper, res);
    }
  }
#endif

#ifdef _BASE_TREAP_COUNT_PREFIX // ^
  inline int _countPrefix(int idx, const KEY& upper) {
    if (idx < 0) {
      return 0;
    }
    const auto& node = _nodes[idx];
    if (node._key < upper) {
      // _BASE_TREAP_COUNT_PREFIX => _BASE_TREAP_SIZE
      return _calcSize(node._lIdx) + 1 + _countPrefix(node._rIdx, upper);
    } else {
      return _countPrefix(node._lIdx, upper);
    }
  }
#endif

#ifdef BASE_TREAP_CALC_SUFFIX // ^
  inline RANGE_V calcSuffix(const KEY& lower) {
    RANGE_V res;
    _initRangeV(res);
    // BASE_TREAP_CALC_SUFFIX => _BASE_TREAP_CALC_SUFFIX
    _calcSuffix(_roots[0], lower, res);
    return res;
  }
#endif

#ifdef _BASE_TREAP_CALC_SUFFIX // ^
  inline void _calcSuffix(int idx, const KEY& lower, RANGE_V& res) {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    if (node._key < lower) {
      _calcSuffix(node._rIdx, lower, res);
    } else {
      if (lower < node._key) {
        _calcSuffix(node._lIdx, lower, res);
      }
      _appendNode(res, node);
      if (node._rIdx >= 0) {
        _appendRange(res, _nodes[node._rIdx]);
      }
    }
  }
#endif

#ifdef BASE_TREAP_CALC_RANGE // ^
  inline const RANGE_V& calcRange(const KEY& lower, const KEY& upper) {
    // BASE_TREAP_CALC_RANGE => _BASE_TREAP_TMP_RANGE_V
    // BASE_TREAP_CALC_RANGE => _BASE_TREAP_CALC_RANGE
    _calcRange(_roots[0], lower, upper, _tmpRangeV);
    return _tmpRangeV;
  }
#endif

#ifdef _BASE_TREAP_CALC_RANGE // ^
  inline void _calcRange(int& idx, const KEY& lower, const KEY& upper, RANGE_V& res) {
    int lIdx, rIdx;
    // _BASE_TREAP_CALC_RANGE => _BASE_TREAP_SPLIT
    _split(idx, upper, lIdx, rIdx);
    _initRangeV(res);
    // _BASE_TREAP_CALC_RANGE => _BASE_TREAP_CALC_SUFFIX
    _calcSuffix(lIdx, lower, res);
    // _BASE_TREAP_CALC_RANGE => _BASE_TREAP_MERGE
    idx = _merge(lIdx, rIdx);
  }
#endif

#ifdef BASE_TREAP_SPLIT_RANGE // ^
  inline void splitRange(const KEY& lower, const KEY& upper, int& lIdx, int& mIdx, int& rIdx) {
    // BASE_TREAP_SPLIT_RANGE => _BASE_TREAP_SPLIT_RANGE
    _splitRange(_roots[0], lower, upper, lIdx, mIdx, rIdx);
  }
#endif

#ifdef _BASE_TREAP_SPLIT_RANGE // ^
  inline void
  _splitRange(int idx, const KEY& lower, const KEY& upper, int& lIdx, int& mIdx, int& rIdx) {
    // _BASE_TREAP_SPLIT_RANGE => _BASE_TREAP_SPLIT
    _split(idx, upper, mIdx, rIdx);
    _split(mIdx, lower, lIdx, mIdx);
  }
#endif

#ifdef BASE_TREAP_MERGE3 // ^
  inline void merge3(int lIdx, int mIdx, int rIdx) {
    // BASE_TREAP_MERGE3 => _BASE_TREAP_MERGE3
    _roots[0] = _merge3(lIdx, mIdx, rIdx);
  }
#endif

#ifdef _BASE_TREAP_MERGE3 // ^
  inline int _merge3(int lIdx, int mIdx, int rIdx) {
    // _BASE_TREAP_MERGE3 => _BASE_TREAP_MERGE
    return _merge(_merge(lIdx, mIdx), rIdx);
  }
#endif

#ifdef _BASE_TREAP_SPLIT // ^
  // Splits into 2 parts, all keys in the left hand side should be smaller than <upper>
  inline void _split(int idx, const KEY& upper, int& lIdx, int& rIdx) {
    if (idx < 0) {
      lIdx = rIdx = -1;
      return;
    }
    auto& node = _nodes[idx];
    if (node._key < upper) {
      _split(node._rIdx, upper, node._rIdx, rIdx);
      lIdx = idx;
    } else {
      _split(node._lIdx, upper, lIdx, node._lIdx);
      rIdx = idx;
    }
    // _BASE_TREAP_SPLIT => _BASE_TREAP_MERGE_V
    _mergeV(_nodes[idx]);
  }
#endif

#ifdef BASE_TREAP_CALC_KTH // ^
  template<typename KTH>
  inline const _Node* calcKth(const KTH& kth) {
    // BASE_TREAP_CALC_KTH => _BASE_TREAP_CALC_KTH
    return _calcKth(_roots[0], kth);
  }
#endif

#ifdef _BASE_TREAP_CALC_KTH // ^
  template<typename KTH>
  inline const _Node* _calcKth(int idx, KTH kth) {
    if (idx < 0 || kth < 0 || !(kth < _nodes[idx]._rangeV)) {
      return nullptr;
    }
    while (true) {
      const auto& node = _nodes[idx];
      if (node._lIdx >= 0) {
        const auto& lNode = _nodes[node._lIdx];
        if (kth < lNode._rangeV) {
          idx = node._lIdx;
          continue;
        }
        kth -= lNode._rangeV;
      }
      RANGE_V tmpRangeV;
      _initRangeV(tmpRangeV);
      _appendNode(tmpRangeV, node);
      if (kth < tmpRangeV) {
        return &node;
      }
      kth -= tmpRangeV;
      idx = node._rIdx;
    }
    return nullptr;
  }
#endif

#ifdef _BASE_TREAP_MERGE_V // ^
  inline void _mergeV(_Node& node) {
    _mergeRangeV(node);
#ifdef _BASE_TREAP_SIZE
    node._size = _calcSize(node._lIdx) + 1 + _calcSize(node._rIdx);
#endif
  }
#endif

#ifdef _BASE_TREAP_SIZE // ^
  inline int _calcSize(int idx) {
    return idx >= 0 ? _nodes[idx]._size : 0;
  }
#endif

  vector<_Node> _nodes;
  vector<int> _roots;
  int _rootCnt;
#ifdef _BASE_TREAP_TMP_RANGE_V
  RANGE_V _tmpRangeV;
#endif
#ifdef _BASE_TREAP_TMP_RANGE_V2
  RANGE_V _tmpRangeV2;
#endif

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const _Node& node) {
    o << "[key:" << node._key << "] (v:" << tostring(node._v)
      << " rangeV:" << tostring(node._rangeV) << " priority:" << node._priority << ")";
    return o;
  }

  inline friend ostream& operator<<(ostream& o, const BaseTreap& treap) {
    o << "total root cnt:" << treap._roots.size();
    vector<bool> toRight;
    unordered_set<int> visited;
    for (int root : treap._roots) {
      treap._output(0, root, toRight, visited, o);
    }
    return o;
  }

  inline void _output(
      int depth, int idx, vector<bool>& toRight, unordered_set<int>& visited, ostream& o) const {
    o << endl;
    FOR(i, 0, SIZE(toRight) - 1) {
      o << (toRight[i] ? ' ' : '|') << "   ";
    }
    if (!toRight.empty()) {
      o << (toRight.back() ? 'L' : '|') << "---";
    }
    if (idx < 0) {
      o << "NULL";
      return;
    }
    const auto& node = _nodes[idx];
    o << node << " @" << idx;
    if (visited.count(idx)) {
      o << " **LOOP**";
      return;
    }
    visited.insert(idx);
    if (node._lIdx >= 0 || node._rIdx >= 0) {
      toRight.push_back(false);
      _output(depth + 1, node._lIdx, toRight, visited, o);
      toRight.back() = true;
      _output(depth + 1, node._rIdx, toRight, visited, o);
      toRight.pop_back();
    }
  }
#endif
};

} // namespace ds
