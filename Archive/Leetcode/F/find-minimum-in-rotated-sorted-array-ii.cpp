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
#define FUNCTION_NAME findMin
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,3,5]
[2,2,2,0,1]
[2,2,2,2,1,2,2]
[2,2,1,2,2,2,2]
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
  int findMin(vector<int>& nums) {
    int n = nums.size();
    int res = nums[n - 1], lower = 0, upper = n - 1;
    while (lower < upper) {
      if (nums[lower] < nums[upper - 1]) {
        MMIN(res, nums[lower]);
        break;
      } else if (nums[lower] == nums[upper - 1]) {
        MMIN(res, nums[lower++]);
      } else {
        int medium = (lower + upper) >> 1;
        if (nums[lower] <= nums[medium]) {
          lower = medium + 1;
        } else {
          MMIN(res, nums[medium]);
          upper = medium;
        }
      }
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
