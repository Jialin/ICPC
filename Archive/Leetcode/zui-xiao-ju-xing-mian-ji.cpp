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
#define FUNCTION_NAME minRecSize
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<int>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[[2,3],[3,0],[4,1]]
[[1,1],[2,3]]
[[1,1],[1,7],[1,17]]
[[5,2],[5,-4],[2,-5],[4,-1],[2,0]]
[[2,0],[4,-3],[2,4],[1,-2],[1,-1]]
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

pair<double, double> calc(int k1, int b1, const vector<int>& line2) {
  double x = (line2[1] - b1) / CAST<double>(k1 - line2[0]);
  return {x, k1 * x + b1};
}

class Solution {
public:
  double minRecSize(vector<vector<int>>& lines) {
    SORT(lines);
    int n = lines.size();
    int lastK, lastMinB, lastMaxB;
    int minB, maxB;

    double minX = 1E100, minY = 1E100;
    double maxX = -1E100, maxY = -1E100;
    bool hasArea = false;

    auto update = [&](double x, double y) {
      hasArea = true;
      MMIN(minX, x);
      MMIN(minY, y);
      MMAX(maxX, x);
      MMAX(maxY, y);
    };

    auto handle = [&](const vector<int>& line, const vector<int>& nxtLine) {
      if (line[0] != lastK) {
        double x, y;
        tie(x, y) = calc(lastK, lastMinB, line);
        update(x, y);
        if (lastMinB != lastMaxB) {
          tie(x, y) = calc(lastK, lastMaxB, line);
          update(x, y);
        }
      }
      MMIN(minB, line[1]);
      MMAX(maxB, line[1]);
      if (line[0] != nxtLine[0]) {
        lastK = line[0];
        lastMinB = minB;
        lastMaxB = maxB;
        minB = maxB = nxtLine[1];
      }
    };

    lastK = lines[0][0];
    minB = maxB = lines[0][1];
    FOR(i, 0, n) {
      handle(lines[i], i == n - 1 ? lines[0] : lines[i + 1]);
    }
    lastK = lines[n - 1][0];
    minB = maxB = lines[n - 1][1];
    for (int i = n - 1; i >= 0; --i) {
      handle(lines[i], i ? lines[i - 1] : lines[n - 1]);
    }

    return hasArea ? (maxX - minX) * (maxY - minY) : 0;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
