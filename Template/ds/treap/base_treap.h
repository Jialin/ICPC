// !macro_gen
// ALL BASE_TREAP_ALL
#pragma once

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
    clear();
  }

#ifdef BASE_TREAP_RESERVE // ^
  inline void reserve(int n) {
    _nodes.reserve(n);
  }
#endif

  inline void clear() {
    _root = -1;
    _nodes.clear();
  }

#ifdef BASE_TREAP_UPDATE // ^
  inline void update(KEY key, const NODE_V& delta) {
    _update(_root, key, delta);
  }

  // Returns whether the parent node need to check rotation
  inline bool _update(int& idx, KEY key, const NODE_V& delta) {
    if (idx < 0) {
      idx = _nodes.size();
      _nodes.emplace_back(key);
      auto& node = _nodes.back();
      _initV(node);
      _updateV(node, delta);
      return true;
    }
    auto& node = _nodes[idx];
    if (node._key == key) {
      _updateV(node, delta);
      return false;
    }
    if (node._key > key) {
      if (_update(node._lIdx, key, delta) && _nodes[node._lIdx]._priority > node._priority) {
        _rotateLeft(idx, node._lIdx);
        return true;
      }
    } else {
      if (_update(node._rIdx, key, delta) && _nodes[node._rIdx]._priority > node._priority) {
        _rotateRight(idx, node._rIdx);
        return true;
      }
    }
    _mergeRangeV(_nodes[idx]);
    return false;
  }

  inline void _rotateLeft(int& idx, int lIdx) {
    auto& node = _nodes[idx];
    auto& lNode = _nodes[lIdx];
    node._lIdx = lNode._rIdx;
    lNode._rIdx = idx;
    _mergeRangeV(node);
    idx = lIdx;
    _mergeRangeV(lNode);
  }

  inline void _rotateRight(int& idx, int rIdx) {
    auto& node = _nodes[idx];
    auto& rNode = _nodes[rIdx];
    _nodes[idx]._rIdx = rNode._lIdx;
    rNode._lIdx = idx;
    _mergeRangeV(node);
    idx = rIdx;
    _mergeRangeV(rNode);
  }
#endif

#ifdef BASE_TREAP_CALC_PREFIX_RETURN // ^
  // Calculates prefix from [-inf, upper1]. NOTE: <upper1> is included
  inline RANGE_V calcPrefix(KEY upper1) {
    RANGE_V res;
    // BASE_TREAP_CALC_PREFIX_RETURN => BASE_TREAP_CALC_PREFIX
    calcPrefix(upper1, res);
    return res;
  }
#endif

#ifdef BASE_TREAP_CALC_PREFIX // ^
  // Calculates prefix from [-inf, upper1]. NOTE: <upper1> is included
  inline void calcPrefix(KEY upper1, RANGE_V& res) {
    _initRangeV(res);
    _calcPrefix(_root, upper1, res);
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
  int _root;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const _Node& node) {
    o << "[key:" << node._key << " v:" << node._v << " rangeV:" << node._rangeV
      << " priority:" << node._priority << " lIdx:" << node._lIdx << " rIdx:" << node._rIdx << "]";
    return o;
  }

  inline friend ostream& operator<<(ostream& o, const BaseTreap& treap) {
    o << "root index:" << treap._root;
    treap._output(0, treap._root, o);
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
