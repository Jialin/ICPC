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
#define FUNCTION_NAME findRadius
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 vector<int>
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,2,3]
 [2]
[1,2,3,4]
[1,4]
[1,5]
[2]
)";
#endif

#include "leetcode/binary_tree_macros.h"
#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    SORT(houses);
    SORT(heaters);
    int res = 0;
    for (int house : houses) {
      auto it = lower_bound(ALL(heaters), house);
      int subRes = numeric_limits<int>::max();
      if (it != heaters.end()) {
        MMIN(subRes, *it - house);
      }
      if (it != heaters.begin()) {
        --it;
        MMIN(subRes, house - *it);
      }
      res = max(res, subRes);
    }
    return res;
  }
};

#ifdef LOCAL

int main() {
  leetcode::handle<Solution>(tests);
  return 0;
}
#endif
