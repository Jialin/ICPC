// !macro_gen
// ALL BASE_TREAP_ALL
#pragma once

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

  inline BaseTreap() : _rootCnt(1) {
    clear();
  }

#ifdef BASE_TREAP_RESERVE_NODES // ^
  inline void reserveNodes(int n) {
    _nodes.reserve(n);
  }
#endif

#ifdef BASE_TREAP_RESERVE_ROOTS // ^
  inline void reserveRoots(int n) {
    _roots.reserve(n);
  }
#endif

  inline void clear() {
    _roots.assign(_rootCnt, -1);
    _nodes.clear();
  }

#ifdef BASE_TREAP_INIT_ROOTS // ^
  inline void initRoots(int rootCnt) {
    _rootCnt = rootCnt;
    clear();
  }
#endif

#ifdef BASE_TREAP_UPDATE // ^
  inline void update(KEY key, const NODE_V& delta, int rootIdx = 0) {
    DEBUG_LT(rootIdx, SIZE(_roots));
    _roots[rootIdx] = _update(_roots[rootIdx], key, delta);
  }

  // Returns the new root index
  inline int _update(int idx, KEY key, const NODE_V& delta) {
    if (idx < 0) {
      idx = _nodes.size();
      _nodes.emplace_back(key);
      auto& node = _nodes.back();
      _initV(node);
      _updateV(node, delta);
      return idx;
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
  inline void erase(KEY key, int rootIdx = 0) {
    DEBUG_LT(rootIdx, SIZE(_roots));
    _roots[rootIdx] = _erase(_roots[rootIdx], key);
  }

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
  // Calculates prefix from [-inf, upper1]. NOTE: <upper1> is included
  inline RANGE_V calcPrefix(KEY upper1, int rootIdx = 0) {
    DEBUG_LT(rootIdx, SIZE(_roots));
    RANGE_V res;
    _initRangeV(res);
    _calcPrefix(_roots[rootIdx], upper1, res);
    return res;
  }

  inline void _calcPrefix(int idx, KEY upper1, RANGE_V& res) {
    if (idx < 0) {
      return;
    }
    const auto& node = _nodes[idx];
    if (node._key > upper1) {
      _calcPrefix(node._lIdx, upper1, res);
    } else {
      if (node._lIdx >= 0) {
        _appendRange(res, _nodes[node._lIdx]);
      }
      _appendNode(res, node);
      if (node._key < upper1) {
        _calcPrefix(node._rIdx, upper1, res);
      }
    }
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
