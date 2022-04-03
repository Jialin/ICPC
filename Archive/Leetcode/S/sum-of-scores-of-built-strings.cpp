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
#define FUNCTION_NAME sumScores
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"babab"
"azbazbzaz"
"aaabbb"
"aaabbbb"
"aaabbbccc"
)";
#endif

#define Z_FUNCTION_INIT

#include "leetcode/linked_list_macros.h"
#include "string/kmp/z_function_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"
#include "string/kmp/z_function.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  long long sumScores(string s) {
    str::ZFunction<char> zfun;
    int n = s.size();
    zfun.init(n, s.data());
    DEBUGV(zfun._prefixs);
    return accumulate(ALL(zfun._prefixs), 0LL);
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
