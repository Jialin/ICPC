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
#define FUNCTION_NAME magicTower
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[100,100,100,-250,-60,-140,-50,-50,100,150]
[-200,-300,400,0]
[-1,-1,10]
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
  int magicTower(vector<int>& nums) {
    if (accumulate(ALL(nums), 1) <= 0) {
      return -1;
    }
    int64_t health = 1;
    priority_queue<int> heap;
    int res = 0;
    for (auto num : nums) {
      health += num;
      if (num < 0) {
        heap.push(-num);
      }
      for (; health <= 0 && !heap.empty(); heap.pop()) {
        health += heap.top();
        ++res;
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
