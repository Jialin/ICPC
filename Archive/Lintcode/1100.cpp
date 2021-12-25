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
#define FUNCTION_NAME strangePrinter
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"aaabbb"
"aba"
"aaabbbcbbbaaa"
"aaabbbabbbabbbbaaaaaaaa"
"abcbcacbbcbbcbbbabcabaacccaaaacb"
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
  int strangePrinter(string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    function<int(int, int)> calc;
    calc = [&](int x, int y) {
      if (x > y) {
        return 0;
      }
      int& res = dp[x][y];
      if (res >= 0) {
        return res;
      }
      res = y - x + 1;
      FOR(i, x, y) {
        MMIN(res, calc(x, i) + calc(i + 1, y) + (s[x] == s[i + 1] ? -1 : 0));
      }
      return res;
    };
    return calc(0, n - 1);
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
