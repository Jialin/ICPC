// !macro_gen
// ALL BASE_COMPACT_SEGMENT_TREE_ALL
#pragma once

#include "common/macros.h"
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "math/bit/next_pow2_32.h"

using namespace std;

namespace ds {

template<
    typename V,
    typename InitV = V,
    typename Update = InitV
#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
    ,
    typename TraverseArgs = nullptr_t
#endif
    >
struct BaseCompactSegmentTree {
  struct Node {
    V v;
    int lower, upper;

    inline bool isValid() const {
      return lower < upper;
    }

    inline bool isLeaf() const {
      return lower + 1 == upper;
    }

#ifdef LOCAL
    inline friend ostream& operator<<(ostream& o, const Node& node) {
      return o << '[' << node.lower << ',' << node.upper << "): " << node.v;
    }
#endif
  };

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  enum Traverse { NONE, LEFT, RIGHT, ALL };
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  virtual inline Traverse _traverse(Node& node, int lower, int upper, TraverseArgs& args) {
    return Traverse::NONE;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  virtual inline bool _mergeAfterTraverse(TraverseArgs& args) {
    return true;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V // ^
  virtual inline void _clearV(V& res) = 0;
#endif
#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V // ^
  virtual inline void _appendV(const Node& node, V& res) = 0;
#endif
  virtual inline void _applyUpdate(const Update& update, Node& node) = 0;
  virtual inline void _initV(InitV initV, Node& node) = 0;
  virtual inline void _mergeV(const Node& lNode, const Node& rNode, V& res) = 0;

#ifdef BASE_COMPACT_SEGMENT_TREE_RESERVE // ^
  inline void reserve(int n) {
    _nodes.reserve(math::nextPow2_32(n) << 1);
  }
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_INIT // ^
  inline void init(vector<InitV> initVs) {
    int n = SIZE(initVs);
    _offset = math::nextPow2_32(n);
    _offsetBit = __builtin_ctz(_offset);
    _nodes.resize(_offset << 1);
    FOR(i, 0, n) {
      auto& node = _nodes[_offset + i];
      node.lower = i;
      node.upper = i + 1;
      _initV(move(initVs[i]), node);
    }
    FOR(i, n, _offset) {
      auto& node = _nodes[_offset + i];
      node.lower = -1;
      node.upper = -2;
    }
    FORR(i, _offset - 1, 1) {
      auto& node = _nodes[i];
      const auto &lNode = _nodes[i << 1], rNode = _nodes[(i << 1) | 1];
      if (lNode.upper == rNode.lower) {
        node.lower = lNode.lower;
        node.upper = rNode.upper;
        _mergeV(lNode, rNode, node.v);
      } else {
        node.lower = -1;
        node.upper = -2;
      }
    }
  }
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_UPDATE // ^
  inline void update(int idx, const Update& update) {
    idx += _offset;
    for (int l = idx, u = idx + 1; l < u; l >>= 1, u >>= 1) {
      if (l & 1) {
        // BASE_COMPACT_SEGMENT_TREE_UPDATE => _BASE_COMPACT_SEGMENT_TREE_APPLY_UPDATE_WRAPPER
        _applyUpdateWrapper(update, _nodes[l++]);
      }
      if (u & 1) {
        _applyUpdateWrapper(update, _nodes[--u]);
      }
    }
    for (int i = __builtin_ctz(idx | (idx + 1)) + 1; i <= _offsetBit; ++i) {
      _mergeVWrapper(idx >> i);
    }
  }
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_CALC_RANGE // ^
  inline V calcRange(int lower, int upper) {
    V res;
    // BASE_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
    _clearV(res);
    // BASE_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
    _calcRange(lower, upper, res);
    return res;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE // ^

  // TODO: to verify
  inline void _calcRange(int lower, int upper, V& res) {
    lower += _offset;
    upper += _offset;
    int bit = 0;
    for (int l = lower; l < (upper >> bit); ++bit, l >>= 1) {
      if (l & 1) {
        // clang-format off
        // _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE => _BASE_COMPACT_SEGMENT_TREE_APPEND_V_WRAPPER
        // clang-format on
        _appendVWrapper(_nodes[l++], res);
      }
    }
    for (--bit; bit >= 0; --bit) {
      int u = upper >> bit;
      if (u & 1) {
        _appendVWrapper(_nodes[u ^ 1], res);
      }
    }
  }
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE // ^
  inline void traverseRange(int lower, int upper, TraverseArgs& args) {
    int lower2 = lower + _offset, upper2 = upper + _offset;
    int bit = 0;
    for (int l = lower2; l < (upper2 >> bit); ++bit, l >>= 1) {
      if (l & 1) {
        // BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE => _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_WRAPPER
        _traverseWrapper(l++, lower, upper, args);
      }
    }
    for (--bit; bit >= 0; --bit) {
      int u = upper2 >> bit;
      if (u & 1) {
        _traverseWrapper(u ^ 1, lower, upper, args);
      }
    }
    if (_mergeAfterTraverse(args)) {
      int lowerCtz1 = __builtin_ctz(lower2) + 1, upperCtz1 = __builtin_ctz(upper2) + 1,
          commonCtz1 = max(lowerCtz1, upperCtz1);
      FOR(i, lowerCtz1, commonCtz1) {
        _mergeVWrapper(lower2 >> i);
      }
      FOR(i, upperCtz1, commonCtz1) {
        _mergeVWrapper((upper2 - 1) >> i);
      }
      for (int i = commonCtz1; i <= _offsetBit; ++i) {
        _mergeVWrapper(lower2 >> i);
        _mergeVWrapper((upper2 - 1) >> i);
      }
    }
  }
#endif

  inline void _mergeVWrapper(int idx) {
    auto& node = _nodes[idx];
    if (node.isValid()) {
      _mergeV(_nodes[idx << 1], _nodes[(idx << 1) | 1], node.v);
    }
  }

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V_WRAPPER // ^
  inline void _appendVWrapper(const Node& node, V& res) {
    if (node.isValid()) {
      // clang-format off
      // _BASE_COMPACT_SEGMENT_TREE_APPEND_V_WRAPPER => _BASE_COMPACT_SEGMENT_TREE_APPEND_V
      // clang-format on
      _appendV(node, res);
    }
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPLY_UPDATE_WRAPPER // ^
  inline void _applyUpdateWrapper(const Update& update, Node& node) {
    if (node.isValid()) {
      _applyUpdate(update, node);
    }
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_WRAPPER // ^
  inline void _traverseWrapper(int idx, int lower, int upper, TraverseArgs& args) {
    auto& node = _nodes[idx];
    // _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_WRAPPER => _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
    Traverse traverse = _traverse(node, lower, upper, args);
    if (traverse == Traverse::NONE || node.isLeaf()) {
      return;
    }
    if (traverse != Traverse::RIGHT) {
      _traverseWrapper(idx << 1, lower, upper, args);
    }
    if (traverse != Traverse::LEFT) {
      _traverseWrapper((idx << 1) | 1, lower, upper, args);
    }
    if (_mergeAfterTraverse(args)) {
      _mergeV(_nodes[idx << 1], _nodes[(idx << 1) | 1], node.v);
    }
  }
#endif

  int _offset, _offsetBit;
  vector<Node> _nodes;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const BaseCompactSegmentTree& st) {
    FOR(i, 1, st._offset << 1) {
      if (st._nodes[i].isValid() && !st._nodes[i >> 1].isValid()) {
        vector<bool> toRight;
        st._output(0, i, toRight, o);
      }
    }
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
    o << node << " @" << idx;
    if (!node.isLeaf()) {
      toRight.push_back(false);
      _output(depth + 1, idx << 1, toRight, o);
      toRight.back() = true;
      _output(depth + 1, (idx << 1) | 1, toRight, o);
      toRight.pop_back();
    }
  }
#endif
};

} // namespace ds
