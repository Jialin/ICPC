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
#define FUNCTION_NAME dayOfYear
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"2019-01-09"
"2019-02-10"
"2003-03-01"
"2004-03-01"
)";
#endif

#include "leetcode/binary_tree_macros.h"
#include "leetcode/linked_list_macros.h"
#define CALENDAR_DAYS_PER_MONTH
#define CALENDAR_IS_LEAP_YEAR
#include "misc/calendar_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"
#include "misc/calendar.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  int dayOfYear(string date) {
    int y, m, d;
    sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d);
    int res = d;
    FOR(i, 0, m - 1) {
      res += misc::DAYS[i];
    }
    if (m > 2 && misc::isLeapYear(y)) {
      ++res;
    }
    return res;
  }
};

#ifdef LOCAL

int main() {
  leetcode::handle<Solution>(tests);
  return 0;
}
#endif
