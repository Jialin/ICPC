// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#ifdef LOCAL
// Typical types:
// - int
// - vector<int>
// - vector<vector<int>>
// - ListNode*
// - TreeNode*
// - Interval
#define FUNCTION_NAME isEvenOddTree
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 TreeNode*
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,10,4,3,null,7,9,12,8,6,null,null,2]
[5,4,2,3,3,7]
[5,9,1,3,5,7]
[1]
[11,8,6,1,3,9,11,30,20,18,16,12,10,4,2,17]
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  bool isEvenOddTree(TreeNode* root) {
    vector<int> vs;

    function<bool(int, TreeNode*)> dfs;
    dfs = [&](int depth, TreeNode* node) {
      if (!node) {
        return true;
      }
      if ((depth & 1) == (node->val & 1)) {
        return false;
      }
      if (depth >= vs.size()) {
        vs.push_back(node->val);
      } else {
        if (depth & 1) {
          if (vs[depth] <= node->val) {
            return false;
          }
        } else {
          if (vs[depth] >= node->val) {
            return false;
          }
        }
        vs[depth] = node->val;
      }
      return dfs(depth + 1, node->left) && dfs(depth + 1, node->right);
    };

    return dfs(0, root);
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
