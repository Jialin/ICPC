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
#define FUNCTION_NAME maxConsecutiveAnswers
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"TTFF"
2
"TFFT"
1
"TTFTTFTT"
1
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
  int maxConsecutiveAnswers(string answerKey, int k) {
    int n = answerKey.size();

    auto calc = [&](char c) {
      int j = 0, cnt = 0, res = 0;
      for (int i = 0; i < n; ++i) {
        for (; j < n && cnt + (answerKey[j] == c) <= k; ++j) {
          cnt += answerKey[j] == c;
        }
        res = max(res, j - i);
        cnt -= answerKey[i] == c;
      }
      return res;
    };

    return max(calc('F'), calc('T'));
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
