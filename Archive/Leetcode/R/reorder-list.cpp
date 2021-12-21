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
#define FUNCTION_NAME reorderList
#define ARGUMENT_CNT 1
#define RETURN_VOID true
#define ARGUMENT_T_1 ListNode*
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,2,3,4]
[1,2,3,4,5]
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
  void reorderList(ListNode* head) {
    if (!head) {
      return;
    }
    auto vs = lc::toVector(head->next);
    auto newVs = vs;
    for (int i = 0, j = vs.size() - 1, k = 0; i <= j; ++k) {
      newVs[k] = (k & 1) ? vs[i++] : vs[j--];
    }
    head->next = lc::fromVector(newVs);
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
