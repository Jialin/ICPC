// !macro_gen
// ALL BASE_TREAP_ALL
#pragma once

#include "common/macros.h"

using namespace std;

namespace ds {

template<typename NODE_V, typename RANGE_V = NODE_V, typename KEY = int>
struct BaseTreap {
  struct _Node {
    KEY _key;
    int _priority, _lIdx, _rIdx;
    NODE_V _v;
    RANGE_V _rangeV;

    inline _Node(KEY key) : _key(key), _priority(rand()), _lIdx(-1), _rIdx(-1) {}
  };

  // Initializes range value
  virtual inline void _initRangeV(RANGE_V& res) = 0;

  // Initializes the values of node
  virtual inline void _initV(_Node& node) = 0;

  // Given delta, updates the values of the node
  virtual inline void _updateV(_Node& node, const NODE_V& delta) = 0;

  // Merges the range value of the node from descendent nodes
  virtual inline void _mergeRangeV(_Node& node) = 0;

  // Appends the node value to the result
  virtual inline void _appendNode(RANGE_V& res, const _Node& idx) = 0;

  // Appends the range value to the result
  virtual inline void _appendRange(RANGE_V& res, const _Node& idx) = 0;

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

#ifdef BASE_TREAP_INIT_ITEMS // ^
  inline void initItems(const vector<pair<KEY, NODE_V>>& vs) {
    // BASE_TREAP_INIT_ITEMS => _BASE_TREAP_INIT_ITEMS
    _roots[0] = _initItems(vs, 0, SIZE(vs));
  }
#endif

#ifdef _BASE_TREAP_INIT_ITEMS // ^
  inline int _initItems(const vector<pair<KEY, NODE_V>>& vs, int from, int to) {
    if (from >= to) {
      return -1;
    }
    int medium = (from + to) >> 1;
    // BASE_TREAP_INIT_ITEMS => _BASE_TREAP_NEW_NODE
    int newIdx = _newNode(vs[medium].first, vs[medium].second);
    _nodes[newIdx]._lIdx = _initItems(vs, from, medium);
    _nodes[newIdx]._rIdx = _initItems(vs, medium + 1, to);
    return _heapify(newIdx);
  }

  inline int _heapify(int idx) {
    if (idx < 0) {
      return -1;
    }
    auto& node = _nodes[idx];
    int lIdx = node._lIdx;
    auto& lNode = _nodes[lIdx];
    int rIdx = node._rIdx;
    auto& rNode = _nodes[rIdx];
    if (lIdx >= 0 && lNode._priority > node._priority &&
        (rIdx < 0 || lNode._priority > rNode._priority)) {
      // BASE_TREAP_INIT_ITEMS => _BASE_TREAP_ROTATE
      _rotateLeft(idx, lIdx);
      return lIdx;
    }
    if (rIdx >= 0 && rNode._priority > node._priority &&
        (lIdx < 0 || rNode._priority > lNode._priority)) {
      _rotateRight(idx, rIdx);
      return rIdx;
    }
    _mergeRangeV(node);
    return idx;
  }
#endif

#ifdef _BASE_TREAP_NEW_NODE // ^
  inline int _newNode(KEY key, const NODE_V& delta) {
    int idx = SIZE(_nodes);
    _nodes.emplace_back(key);
    auto& node = _nodes.back();
    _initV(node);
    _updateV(node, delta);
    return idx;
  }
#endif

#ifdef BASE_TREAP_UPDATE // ^
  inline void update(KEY key, const NODE_V& delta) {
    // BASE_TREAP_UPDATE => _BASE_TREAP_UPDATE
    _roots[0] = _update(_roots[0], key, delta);
  }
#endif

#ifdef _BASE_TREAP_UPDATE // ^
  // Returns the new root index
  inline int _update(int idx, KEY key, const NODE_V& delta) {
    if (idx < 0) {
      // _BASE_TREAP_UPDATE => _BASE_TREAP_NEW_NODE
      return _newNode(key, delta);
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      _updateV(node, delta);
      return idx;
    }
    if (node._key > key) {
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
    _mergeRangeV(_nodes[idx]);
    return idx;
  }
#endif

#ifdef _BASE_TREAP_ROTATE // ^
  inline void _rotateLeft(int idx, int lIdx) {
    auto& node = _nodes[idx];
    auto& lNode = _nodes[lIdx];
    node._lIdx = lNode._rIdx;
    lNode._rIdx = idx;
    _mergeRangeV(node);
    idx = lIdx;
    _mergeRangeV(lNode);
  }

  inline void _rotateRight(int idx, int rIdx) {
    auto& node = _nodes[idx];
    auto& rNode = _nodes[rIdx];
    node._rIdx = rNode._lIdx;
    rNode._lIdx = idx;
    _mergeRangeV(node);
    idx = rIdx;
    _mergeRangeV(rNode);
  }
#endif

#ifdef BASE_TREAP_ERASE // ^
  inline void erase(KEY key) {
    // BASE_TREAP_ERASE => _BASE_TREAP_ERASE
    _roots[0] = _erase(_roots[0], key);
  }
#endif

#ifdef _BASE_TREAP_ERASE // ^
  inline int _erase(int idx, KEY key) {
    if (idx < 0) {
      return -1;
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      return _merge(node._lIdx, node._rIdx);
    }
    if (node._key > key) {
      node._lIdx = _erase(node._lIdx, key);
    } else {
      node._rIdx = _erase(node._rIdx, key);
    }
    _mergeRangeV(node);
    return idx;
  }

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
      _mergeRangeV(lNode);
      return lIdx;
    } else {
      rNode._lIdx = _merge(lIdx, rNode._lIdx);
      _mergeRangeV(rNode);
      return rIdx;
    }
  }
#endif

#ifdef BASE_TREAP_CALC_PREFIX // ^
  // Calculates prefix from (-inf, upper_1] (i.e. (-inf, upper)). NOTE: <upper_1> is included
  inline RANGE_V calcPrefix(KEY upper_1) {
    RANGE_V res;
    _initRangeV(res);
    // BASE_TREAP_CALC_PREFIX => _BASE_TREAP_CALC_PREFIX
    _calcPrefix(_roots[0], upper_1, res);
    return res;
  }
#endif

#ifdef _BASE_TREAP_CALC_PREFIX // ^
  inline void _calcPrefix(int idx, KEY upper_1, RANGE_V& res) {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    if (node._key > upper_1) {
      _calcPrefix(node._lIdx, upper_1, res);
    } else {
      if (node._lIdx >= 0) {
        _appendRange(res, _nodes[node._lIdx]);
      }
      _appendNode(res, node);
      if (node._key < upper_1) {
        _calcPrefix(node._rIdx, upper_1, res);
      }
    }
  }
#endif

#ifdef BASE_TREAP_CALC_SUFFIX // ^
  inline RANGE_V calcSuffix(KEY lower) {
    RANGE_V res;
    _initRangeV(res);
    // BASE_TREAP_CALC_SUFFIX => _BASE_TREAP_CALC_SUFFIX
    _calcSuffix(_roots[0], lower, res);
    return res;
  }
#endif

#ifdef _BASE_TREAP_CALC_SUFFIX // ^
  inline void _calcSuffix(int idx, KEY lower, RANGE_V& res) {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    if (node._key < lower) {
      _calcSuffix(node._rIdx, lower, res);
    } else {
      if (node._key > lower) {
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
  inline RANGE_V calcRange(KEY lower, KEY upper) {
    RANGE_V res;
    _initRangeV(res);
    _calcRange(_roots[0], lower, upper, res);
    return res;
  }
#endif

#ifdef _BASE_TREAP_CALC_RANGE // ^
  inline void _calcRange(int idx, KEY lower, KEY upper, RANGE_V& res) {
    // TODO: WIP
  }
#endif

  vector<_Node> _nodes;
  vector<int> _roots;
  int _rootCnt;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const _Node& node) {
    o << "[key:" << node._key << " v:" << node._v << " rangeV:" << node._rangeV
      << " priority:" << node._priority << " lIdx:" << node._lIdx << " rIdx:" << node._rIdx << "]";
    return o;
  }

  inline friend ostream& operator<<(ostream& o, const BaseTreap& treap) {
    o << "total root cnt:" << treap._roots.size();
    for (int root : treap._roots) {
      treap._output(0, root, o);
    }
    return o;
  }

  inline void _output(int depth, int idx, ostream& o) const {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    o << endl << string(depth, '\t') << "idx:" << idx << ' ' << node;
    _output(depth + 1, node._lIdx, o);
    _output(depth + 1, node._rIdx, o);
  }
#endif
};

} // namespace ds