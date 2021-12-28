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
#define FUNCTION_NAME fractionToDecimal
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 int
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
1
2
2
1
2
3
4
333
1
5
1
999000
-1
-999000
1
-999000
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
  string fractionToDecimal(int num0, int den0) {
    stringstream ss;
    int64_t num = num0, den = den0;
    if (den < 0) {
      num = -num;
      den = -den;
    }
    if (num < 0) {
      ss << '-';
      num = -num;
    }
    ss << num / den;
    num %= den;
    if (!num) {
      return ss.str();
    }
    unordered_map<int64_t, int> vs;
    vs[num] = 0;
    int idx = 0;
    stringstream subSs;
    while (true) {
      num *= 10;
      subSs << CAST<char>('0' + num / den);
      num %= den;
      if (!num || vs.count(num)) {
        break;
      }
      vs[num] = ++idx;
    }
    if (num) {
      string decimal = subSs.str();
      int v = vs[num];
      return ss.str() + '.' + decimal.substr(0, v) + '(' + decimal.substr(v) + ')';
    } else {
      return ss.str() + '.' + subSs.str();
    }
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
