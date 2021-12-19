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
#define FUNCTION_NAME hasCycle
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 ListNode*
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[3,2,0,-4]:1
[1,2]:0
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
  bool hasCycle(ListNode* head) {
    if (!head) {
      return false;
    }
    auto* slow = head;
    auto* fast = head->next;
    while (fast && slow != fast) {
      if (!fast->next) {
        return false;
      }
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow == fast;
  }
};

#ifdef LOCAL

int main() {
  leetcode::handle<Solution>(tests);
  return 0;
}
#endif
