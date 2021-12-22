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
#define FUNCTION_NAME repeatedStringMatch
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 string
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"abcd"
"cdabcdab"
"a"
"aa"
"a"
"a"
"abc"
"wxyz"
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
  int repeatedStringMatch(string a, string b) {
    int n = a.size(), m = b.size();
    int cnt = (m + n - 1) / n;
    stringstream ss;
    FOR(i, 0, cnt) {
      ss << a;
    }
    if (ss.str().find(b) != string::npos) {
      return cnt;
    }
    ss << a;
    return ss.str().find(b) != string::npos ? cnt + 1 : -1;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
