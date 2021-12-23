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
#define FUNCTION_NAME maxProduct
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[2,3,-2,4]
[-2,0,-1]
[-2]
[-2,3,-4]
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
  int maxProduct(vector<int>& nums) {
    int minP, maxP, res;
    minP = maxP = res = nums[0];
    FOR(i, 1, SIZE(nums)) {
      int tmpMinP = minP;
      minP = min(min(minP * nums[i], maxP * nums[i]), nums[i]);
      maxP = max(max(maxP * nums[i], tmpMinP * nums[i]), nums[i]);
      MMAX(res, maxP);
    }
    return res;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
