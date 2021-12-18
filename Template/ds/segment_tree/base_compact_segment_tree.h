// !macro_gen
// ALL BASE_COMPACT_SEGMENT_TREE_ALL
#pragma once

#include "ds/segment_tree/base_compact_segment_tree_macros.h"

using namespace std;

namespace ds {

template<typename V>
struct BaseCompactSegmentTree {
  struct _Node {
    V v;

#ifdef LOCAL
    inline friend ostream& operator<<(ostream& o, const _Node& node) {
      o << tostring(node.v);
      return o;
    }
#endif
  };

  virtual inline void _mergeVs(const _Node& lNode, const _Node& rNode, V& res) = 0;
  virtual inline void _initV(V& res) = 0;
  virtual inline void _append(const _Node& node, V& res) = 0;

#ifdef BASE_COMPACT_SEGMENT_TREE_RESERVE // ^
  inline void reserve(int n) {
    _nodes.reserve(n << 1);
  }
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_INIT // ^
  inline void init(vector<V> leafVs) {
    _n = leafVs.size();
    _nodes.resize(_n << 1);
    // BASE_COMPACT_SEGMENT_TREE_INIT => _BASE_COMPACT_SEGMENT_TREE_INIT
    _init(0, 0, _n, leafVs);
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_INIT // ^
  inline void _init(int idx, int lower, int upper, vector<V>& leafVs) {
    auto& node = _nodes[idx];
    if (lower + 1 == upper) {
      node.v = move(leafVs[lower]);
      return;
    }
    int medium = (lower + upper) >> 1;
    _init(idx + 1, lower, medium, leafVs);
    int rIdx = idx + ((medium - lower) << 1);
    _init(rIdx, medium, upper, leafVs);
    _mergeVs(_nodes[idx + 1], _nodes[rIdx], node.v);
  }
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_CALC_RANGE // ^
  inline V calcRange(int lower, int upper) {
    V res;
    _initV(res);
    // BASE_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
    _calcRange(0, 0, _n, lower, upper, res);
    return res;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE // ^
  inline void _calcRange(int idx, int lower, int upper, int subLower, int subUpper, V& res) {
    if (subLower <= lower && upper <= subUpper) {
      _append(_nodes[idx], res);
      return;
    }
    int medium = (lower + upper) >> 1;
    if (subLower < medium) {
      _calcRange(idx + 1, lower, medium, subLower, subUpper, res);
    }
    if (medium < subUpper) {
      _calcRange(idx + ((medium - lower) << 1), medium, upper, subLower, subUpper, res);
    }
  }
#endif

  int _n;
  vector<_Node> _nodes;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const BaseCompactSegmentTree& st) {
    vector<bool> toRight;
    st._output(0, 0, 0, st._n, toRight, o);
    return o;
  }

  inline void
  _output(int depth, int idx, int lower, int upper, vector<bool>& toRight, ostream& o) const {
    o << endl;
    FOR(i, 0, SIZE(toRight) - 1) {
      o << (toRight[i] ? ' ' : '|') << "   ";
    }
    if (!toRight.empty()) {
      o << (toRight.back() ? 'L' : '|') << "---";
    }
    o << '[' << lower << ',' << upper << "): " << tostring(_nodes[idx]) << " @" << idx;
    if (upper - lower > 1) {
      int medium = (lower + upper) >> 1;
      toRight.push_back(false);
      _output(depth + 1, idx + 1, lower, medium, toRight, o);
      toRight.back() = true;
      _output(depth + 1, idx + ((medium - lower) << 1), medium, upper, toRight, o);
      toRight.pop_back();
    }
  }
#endif
};

} // namespace ds
