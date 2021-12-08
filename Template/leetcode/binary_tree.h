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

  inline friend void _output(int depth, const TreeNode* node, vector<bool>& toRight, ostream& o) {
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
    if (!node->left && !node->right) {
      return;
    }
    toRight.push_back(false);
    _output(depth + 1, node->left, toRight, o);
    toRight.back() = true;
    _output(depth + 1, node->right, toRight, o);
    toRight.pop_back();
  }

  inline friend ostream& operator<<(ostream& o, const TreeNode* node) {
    vector<bool> toRight;
    _output(0, node, toRight, o);
    return o;
  }
};
#endif
