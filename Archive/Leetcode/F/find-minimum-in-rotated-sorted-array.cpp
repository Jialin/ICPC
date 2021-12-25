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
[3,4,5,1,2]
[4,5,6,7,0,1,2]
[11,13,15,17]
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
    int res = n - 1, lower = 0, upper = n - 1;
    while (lower < upper) {
      int medium = (lower + upper) >> 1;
      if (nums[medium] < nums[n - 1]) {
        res = medium;
        upper = medium;
      } else {
        lower = medium + 1;
      }
    }
    return nums[res];
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
