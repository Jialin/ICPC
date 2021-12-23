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
#define FUNCTION_NAME maxPoints
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<int>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[[1,1],[2,2],[3,3]]
[[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
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
  int maxPoints(vector<vector<int>>& points) {
    int n = points.size();
    if (n == 1) {
      return 1;
    }
    vector<double> angles;
    int res = 0;
    FOR(i, 0, n) {
      angles.clear();
      FORIF(j, 0, n, i != j) {
        angles.push_back(atan2(points[j][1] - points[i][1], points[j][0] - points[i][0]));
      }
      SORT(angles);
      int subRes = 1, cnt = 1;
      FOR(i, 1, n - 1) {
        if (angles[i] - angles[i - 1] < 1E-8) {
          MMAX(subRes, ++cnt);
        } else {
          cnt = 1;
        }
      }
      MMAX(res, subRes);
    }
    return res + 1;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
