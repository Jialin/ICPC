// !macro_gen
// ALL BASE_LAZY_COMPACT_SEGMENT_TREE_ALL
#pragma once

#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

using namespace std;

namespace ds {

template<typename V, typename InitV = V, typename Update = InitV>
struct BaseLazyCompactSegmentTree {
  struct _Node {
    V v;
    Update update;
    int lower, upper;

    inline int lSize() const {
      return (upper - lower) & ~1;
    }

    inline bool isLeaf() const {
      return lower + 1 == upper;
    }
  };

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V // ^
  virtual inline void _clearV(V& res) = 0;
#endif
#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V // ^
  virtual inline void _appendV(const _Node& node, V& res) = 0;
#endif
  virtual inline bool _hasUpdate(_Node& node) = 0;
  virtual inline void _applyUpdate(const Update& update, _Node& node) = 0;
  virtual inline void _clearUpdate(_Node& node) = 0;
  virtual inline void _initV(InitV initV, _Node& node) = 0;
  virtual inline void _mergeV(const _Node& lNode, const _Node& rNode, V& res) = 0;

#ifdef BASE_LAZY_COMPACT_SEGMENT_TREE_RESERVE // ^
  inline void reserve(int n) {
    _nodes.reserve(n << 1);
  }
#endif

#ifdef BASE_LAZY_COMPACT_SEGMENT_TREE_INIT // ^
  inline void init(vector<InitV> leafVs) {
    _n = leafVs.size();
    _nodes.resize(_n << 1);
    // BASE_LAZY_COMPACT_SEGMENT_TREE_INIT => _BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
    _init(0, 0, _n, leafVs);
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_INIT // ^
  inline void _init(int idx, int lower, int upper, vector<InitV>& leafVs) {
    auto& node = _nodes[idx];
    node.lower = lower;
    node.upper = upper;
    _clearUpdate(node);
    if (lower + 1 == upper) {
      _initV(move(leafVs[lower]), node);
      return;
    }
    int medium = (lower + upper) >> 1;
    _init(idx + 1, lower, medium, leafVs);
    int rIdx = idx + node.lSize();
    _init(rIdx, medium, upper, leafVs);
    _mergeV(_nodes[idx + 1], _nodes[rIdx], node.v);
  }
#endif

#ifdef BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE // ^
  inline void updateRange(int lower, int upper, const Update& update) {
    // BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE => _BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
    _updateRange(0, lower, upper, update);
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE // ^
  inline void _updateRange(int idx, int lower, int upper, const Update& update) {
    if (lower >= upper) {
      return;
    }
    auto& node = _nodes[idx];
    if (lower <= node.lower && node.upper <= upper) {
      _applyUpdate(update, node);
      return;
    }
    int medium = (node.lower + node.upper) >> 1;
    int rIdx = idx + node.lSize();
    if (_hasUpdate(node)) {
      _applyUpdate(node.update, _nodes[idx + 1]);
      _applyUpdate(node.update, _nodes[rIdx]);
      _clearUpdate(node);
    }
    if (lower < medium) {
      _updateRange(idx + 1, lower, upper, update);
    }
    if (medium < upper) {
      _updateRange(rIdx, lower, upper, update);
    }
    _mergeV(_nodes[idx + 1], _nodes[rIdx], node.v);
  }
#endif

#ifdef BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE // ^
  inline V calcRange(int lower, int upper) {
    V res;
    // BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
    _clearV(res);
    // BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
    _calcRange(0, lower, upper, res);
    return res;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE // ^
  inline void _calcRange(int idx, int lower, int upper, V& res) {
    if (lower >= upper) {
      return;
    }
    auto& node = _nodes[idx];
    if (lower <= node.lower && node.upper <= upper) {
      // _BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
      _appendV(node, res);
      return;
    }
    int medium = (node.lower + node.upper) >> 1;
    int rIdx = idx + node.lSize();
    bool hasUpdate = _hasUpdate(node);
    if (hasUpdate) {
      _applyUpdate(node.update, _nodes[idx + 1]);
      _applyUpdate(node.update, _nodes[rIdx]);
      _clearUpdate(node);
    }
    if (lower < medium) {
      _calcRange(idx + 1, lower, upper, res);
    }
    if (medium < upper) {
      _calcRange(rIdx, lower, upper, res);
    }
    if (hasUpdate) {
      _mergeV(_nodes[idx + 1], _nodes[rIdx], node.v);
    }
  }
#endif

  int _n;
  vector<_Node> _nodes;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const _Node& node) {
    o << tostring2("v", node.v, "update", node.update);
    return o;
  }

  inline friend ostream& operator<<(ostream& o, const BaseLazyCompactSegmentTree& st) {
    vector<bool> toRight;
    st._output(0, 0, toRight, o);
    return o;
  }

  inline void _output(int depth, int idx, vector<bool>& toRight, ostream& o) const {
    o << endl;
    FOR(i, 0, SIZE(toRight) - 1) {
      o << (toRight[i] ? ' ' : '|') << "   ";
    }
    if (!toRight.empty()) {
      o << (toRight.back() ? 'L' : '|') << "---";
    }
    const auto& node = _nodes[idx];
    o << '[' << node.lower << ',' << node.upper << "): " << node << " @" << idx;
    if (!node.isLeaf()) {
      toRight.push_back(false);
      _output(depth + 1, idx + 1, toRight, o);
      toRight.back() = true;
      _output(depth + 1, idx + node.lSize(), toRight, o);
      toRight.pop_back();
    }
  }
#endif
};

} // namespace ds
