// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define LEETCODE_LINKED_LIST_CALC_KTH
#define LEETCODE_LINKED_LIST_CALC_LENGTH
#include "leetcode/linked_list_macros.h"

#include "leetcode/linked_list.h"
#include "leetcode/parse.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  ListNode* deleteMiddle(ListNode* head) {
    ListNode dummy;
    dummy.next = head;
    auto* node = leetcode::calcKth(&dummy, leetcode::calcLength(head) >> 1);
    if (node && node->next) {
      node->next = node->next->next;
    }
    return dummy.next;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  {
    auto v1 = leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
    auto res = Solution().deleteMiddle(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseLinkedList("[1,2,3,4]");
    auto res = Solution().deleteMiddle(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseLinkedList("[3,2,1]");
    auto res = Solution().deleteMiddle(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseLinkedList("[2,1]");
    auto res = Solution().deleteMiddle(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseLinkedList("[1]");
    auto res = Solution().deleteMiddle(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
