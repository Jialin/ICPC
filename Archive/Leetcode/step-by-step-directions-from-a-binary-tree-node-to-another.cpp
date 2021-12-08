// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "leetcode/binary_tree_macros.h"
#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/linked_list.h"
#include "leetcode/parse.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  string getDirections(TreeNode* root, int startValue, int destValue) {
    DEBUGF("====0\n");
    DEBUGV(root);
    DEBUGF("====1\n");
    unordered_map<int, TreeNode*> lookup;
    unordered_map<int, TreeNode*> parents;
    unordered_map<int, int> depths;

    function<void(int, TreeNode*, TreeNode*)> dfs;
    dfs = [&](int depth, TreeNode* node, TreeNode* parent) {
      if (!node) {
        return;
      }
      lookup[node->val] = node;
      depths[node->val] = depth;
      parents[node->val] = parent;
      dfs(depth + 1, node->left, node);
      dfs(depth + 1, node->right, node);
    };
    dfs(0, root, nullptr);

    stringstream lss, rss;
    while (startValue != destValue) {
      if (depths[startValue] > depths[destValue]) {
        lss << 'U';
        startValue = parents[startValue]->val;
      } else {
        auto* p = parents[destValue];
        auto* node = lookup[destValue];
        rss << (p->left == node ? 'L' : 'R');
        destValue = parents[destValue]->val;
      }
    }

    string res;
    rss >> res;
    reverse(ALL(res));
    return lss.str() + res;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
    auto res = Solution().getDirections(v1, 3, 6);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseBinaryTree("[2,1]");
    auto res = Solution().getDirections(v1, 2, 1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
