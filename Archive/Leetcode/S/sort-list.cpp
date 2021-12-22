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
#define FUNCTION_NAME sortList
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 ListNode*
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[4,2,1,3]
[-1,5,3,4,0]
[]
)";
#endif

#define LEETCODE_LINKED_LIST_FROM_VECTOR
#define LEETCODE_LINKED_LIST_TO_VECTOR
#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  ListNode* sortList(ListNode* head) {
    auto vs = lc::toVector(head);
    SORT(vs);
    return lc::fromVector(vs);
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
