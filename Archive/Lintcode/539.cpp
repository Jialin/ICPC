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
#define FUNCTION_NAME moveZeroes
#define ARGUMENT_CNT 1
#define RETURN_VOID true
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[0, 1, 0, 3, 12],
[0, 0, 0, 3, 1]
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
  void moveZeroes(vector<int>& nums) {
    int n = nums.size();
    int pnt = 0;
    FORIF(i, 0, n, nums[i]) {
      swap(nums[pnt++], nums[i]);
    }
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
