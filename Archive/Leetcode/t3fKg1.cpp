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
#define FUNCTION_NAME processTasks
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<int>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[[1,3,2],[2,5,3],[5,6,2]]
[[2,3,1],[5,5,1],[5,6,2]]
[[29,70,3],[43,48,3],[30,83,27],[6,75,26],[25,96,41],[2,80,44],[74,88,15],[52,97,17],[33,50,2],[66,82,8]]
[[61,96,34],[1,59,18],[33,69,32],[36,86,9],[46,59,6],[33,99,31],[14,33,8],[63,66,1]]
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
  int processTasks(vector<vector<int>>& tasks) {
    sort(ALL(tasks), [](const auto& x, const auto& y) {
      return x[1] < y[1];
    });
    vector<pair<pair<int, int>, int>> intervals;
    intervals.reserve(SIZE(tasks));
    for (const auto& task : tasks) {
      int start = task[0], end = task[1], period = task[2];
      const auto it = lower_bound(ALL(intervals), make_pair(make_pair(start, -1), 0));
      if (it != intervals.end()) {
        period -= (intervals.empty() ? 0 : intervals.back().second) - it->second +
                  (it->first.first - max(it->first.second, start) + 1);
      }
      if (period > 0) {
        int lastEnd = end;
        for (; !intervals.empty() && lastEnd - intervals.back().first.first <= period;
             intervals.pop_back()) {
          period -= lastEnd - intervals.back().first.first;
          lastEnd = intervals.back().first.second - 1;
        }
        int newStart = lastEnd - period + 1;
        intervals.emplace_back(
            make_pair(end, newStart),
            (intervals.empty() ? 0 : intervals.back().second) + end - newStart + 1);
      }
    }
    return intervals.back().second;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
