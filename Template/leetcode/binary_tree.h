// !macro_gen
// ALL LEETCODE_BINARY_TREE_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

#ifdef LOCAL
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

  inline bool _containsLoop(unordered_set<int64_t>& visited) const {
    auto address = int64_t(this);
    if (visited.count(address)) {
      return true;
    }
    visited.insert(address);
    if (left && left->_containsLoop(visited)) {
      return true;
    }
    if (right && right->_containsLoop(visited)) {
      return true;
    }
    return false;
  }

  inline friend void _output(
      int depth,
      const TreeNode* node,
      bool containsLoop,
      vector<bool>& toRight,
      unordered_set<int64_t>& visited,
      ostream& o) {
    o << endl;
    FOR(i, 0, SIZE(toRight) - 1) {
      o << (toRight[i] ? ' ' : '|');
      o << "   ";
    }
    if (!toRight.empty()) {
      o << (toRight.back() ? 'L' : '|');
      o << "---";
    }
    if (node) {
      o << '[' << node->val << ']';
    } else {
      o << "NULL";
      return;
    }
    auto address = int64_t(node);
    if (containsLoop) {
      o << "(@" << hex << address << dec << ')';
    }
    if (visited.count(address)) {
      o << "**LOOP**";
      return;
    }
    visited.insert(address);
    if (!node->left && !node->right) {
      return;
    }
    toRight.push_back(false);
    _output(depth + 1, node->left, containsLoop, toRight, visited, o);
    toRight.back() = true;
    _output(depth + 1, node->right, containsLoop, toRight, visited, o);
    toRight.pop_back();
  }

  inline friend ostream& operator<<(ostream& o, const TreeNode* node) {
    unordered_set<int64_t> visited;
    auto containsLoop = node->_containsLoop(visited);
    visited.clear();
    vector<bool> toRight;
    _output(0, node, containsLoop, toRight, visited, o);
    return o;
  }
};
#endif
