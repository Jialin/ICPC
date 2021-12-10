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
  int maxPathSum(TreeNode* root) {
    function<pair<int, int>(TreeNode*)> dfs;
    dfs = [&](TreeNode* u) -> pair<int, int> {
      if (!u) {
        return {0, 0};
      }
      auto l = dfs(u->left);
      auto r = dfs(u->right);
      int down = max(max(l.second, r.second), 0) + u->val;
      int path = max(down, max(l.second, 0) + u->val + max(r.second, 0));
      if (u->left) {
        path = max(path, l.first);
      }
      if (u->right) {
        path = max(path, r.first);
      }
      return {path, down};
    };

    return dfs(root).first;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseBinaryTree("[1,2,3]");
    auto res = Solution().maxPathSum(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseBinaryTree("[-10,9,20,null,null,15,7]");
    auto res = Solution().maxPathSum(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseBinaryTree("[-3]");
    auto res = Solution().maxPathSum(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
