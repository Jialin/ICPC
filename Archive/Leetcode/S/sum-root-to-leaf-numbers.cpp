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
  int sumNumbers(TreeNode* root) {
    int res = 0, subRes = 0;

    function<void(TreeNode*)> dfs;
    dfs = [&](TreeNode* node) {
      if (!node) {
        return;
      }
      subRes = subRes * 10 + node->val;
      if (node->left || node->right) {
        dfs(node->left);
        dfs(node->right);
      } else {
        res += subRes;
      }
      subRes /= 10;
    };
    dfs(root);

    return res;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<Interval>("[(1,3),(2,6),(8,10),(15,18)]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseBinaryTree("[1,2,3]");
    auto res = Solution().sumNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseBinaryTree("[4,9,0,5,1]");
    auto res = Solution().sumNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
