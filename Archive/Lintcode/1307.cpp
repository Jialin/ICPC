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
#define FUNCTION_NAME verifyPreorder
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,3,2]
[1,2]
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
  bool verifyPreorder(vector<int>& preorder) {
    function<bool(int, int)> dfs;
    dfs = [&](int lower, int upper) {
      if (lower >= upper) {
        return true;
      }
      auto it = find_if(preorder.begin() + lower + 1, preorder.begin() + upper, [&](int v) {
        return v > preorder[lower];
      });
      return all_of(
                 it,
                 preorder.begin() + upper,
                 [&](int v) {
                   return v > preorder[lower];
                 }) &&
             dfs(lower + 1, it - preorder.begin()) && dfs(it - preorder.begin(), upper);
    };
    return dfs(0, preorder.size());
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
