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
#define FUNCTION_NAME maxValue
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 TreeNode*
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[5,2,3,4]
2
[4,1,3,9,null,null,2]
2
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

vector<int> dfs(const TreeNode* node, int bound) {
  vector<int> res(bound + 1);
  if (!node) {
    return res;
  }
  const auto& lRes = dfs(node->left, bound);
  const auto& rRes = dfs(node->right, bound);
  res[0] = *max_element(ALL(lRes)) + *max_element(ALL(rRes));
  FOR(i, 0, bound + 1) FOR(j, 0, bound - i) {
    MMAX(res[i + j + 1], lRes[i] + rRes[j] + node->val);
  }
  return res;
}

class Solution {
public:
  int maxValue(TreeNode* root, int k) {
    const auto& res = dfs(root, k);
    return *max_element(ALL(res));
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
