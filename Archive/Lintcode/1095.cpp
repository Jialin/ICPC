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
#define FUNCTION_NAME maximumSwap
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 int
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
2736
9973
19999
9678676
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
  int maximumSwap(int num) {
    if (num < 10) {
      return num;
    }
    vector<int> digits;
    for (int v = num; v; v /= 10) {
      digits.push_back(v % 10);
    }
    int n = digits.size();
    int resIdx = -1, resIdx2 = -1;
    int maxDIdx = 0;
    FOR(i, 0, n - 1) {
      if (digits[maxDIdx] < digits[i]) {
        maxDIdx = i;
      }
      if (digits[maxDIdx] > digits[i + 1]) {
        resIdx = i + 1;
        resIdx2 = maxDIdx;
      }
    }
    if (resIdx < 0) {
      return num;
    }
    swap(digits[resIdx], digits[resIdx2]);
    int res = 0;
    FORR(i, n - 1, 0) {
      res = res * 10 + digits[i];
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
