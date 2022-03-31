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
#define FUNCTION_NAME escapeMaze
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<string>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[[".#.","#.."],["...",".#."],[".##",".#."],["..#",".#."]]
[[".#.","..."],["...","..."]]
[["...","...","..."],[".##","###","##."],[".##","###","##."],[".##","###","##."],[".##","###","##."],[".##","###","##."],[".##","###","##."]]
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

const int MAXN = 50;

bool dp[2][2][3][MAXN][MAXN];

class Solution {
public:
  bool escapeMaze(vector<vector<string>>& maze) {
    int n = maze[0].size(), m = maze[0][0].size();
    if (n == 1 && m == 1) {
      return true;
    }

    int t = 0;
    auto update = [&](int round, int skill1, int skill2, int i, int j, bool stay) {
      if (i < 0 || i >= n || j < 0 || j >= m) {
        return;
      }
      if (maze[round][i][j] == '.') {
        dp[t ^ 1][skill1][!stay && skill2 == 1 ? 2 : skill2][i][j] = true;
        return;
      }
      if (!skill1) {
        // use skill1
        dp[t ^ 1][1][skill2][i][j] = true;
      }
      if (!skill2) {
        // start skill2
        dp[t ^ 1][skill1][1][i][j] = true;
      } else if (stay && skill2 == 1) {
        // continue using skill2
        dp[t ^ 1][skill1][skill2][i][j] = true;
      }
    };

    memset(dp, 0, sizeof(dp));
    dp[t][0][0][0][0] = true;
    FOR(round, 1, maze.size()) {
      memset(dp[t ^ 1], 0, sizeof(dp[t ^ 1]));
      FOR(skill1, 0, 2) FOR(skill2, 0, 3) FOR(i, 0, n) FORIF(j, 0, m, dp[t][skill1][skill2][i][j]) {
        update(round, skill1, skill2, i - 1, j, false);
        update(round, skill1, skill2, i + 1, j, false);
        update(round, skill1, skill2, i, j, true);
        update(round, skill1, skill2, i, j - 1, false);
        update(round, skill1, skill2, i, j + 1, false);
      }
      t ^= 1;
      FOR(skill1, 0, 2) FORIF(skill2, 0, 3, dp[t][skill1][skill2][n - 1][m - 1]) {
        return true;
      }
    }
    return false;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
