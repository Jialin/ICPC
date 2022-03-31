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
#define FUNCTION_NAME maxGroupNumber
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[2,2,2,3,4]
[2,2,2,3,4,1,3]
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

const int MAXN = 7;

class Solution {
public:
  int maxGroupNumber(vector<int>& tiles) {
    SORT(tiles);
    int n = tiles.size();
    int dp[2][MAXN][MAXN];
    int t = 0;
    memset(dp[t], 0xFF, sizeof(dp[t]));
    dp[t][0][0] = 0;
    int lastV1 = -200, lastV2 = -100;
    int cnt = 1;
    FOR(i, 0, n) {
      if (i == n - 1 || tiles[i] != tiles[i + 1]) {
        int baseDelta = max(cnt / 3 - 1 - !(cnt % 3), 0);
        cnt -= baseDelta * 3;
        // DEBUGVS(baseDelta, cnt + baseDelta * 3, cnt, tiles[i]);
        memset(dp[t ^ 1], 0xFF, sizeof(dp[t ^ 1]));
        if (lastV1 + 1 == lastV2 && lastV2 + 1 == tiles[i]) {
          // DEBUGV("a");
          FOR(x, 0, MAXN) FORIF(y, 0, MAXN, dp[t][x][y] >= 0) {
            int delta = min(min(x, y), cnt);
            FOR(d, 0, delta + 1) {
              MMAX(dp[t ^ 1][y - d][cnt - d], dp[t][x][y] + baseDelta + d);
            }
          }
          lastV1 = lastV2;
        } else if (lastV2 + 1 == tiles[i]) {
          // DEBUGV("b");
          FOR(x, 0, MAXN) FORIF(y, 0, MAXN, dp[t][x][y] >= 0) {
            MMAX(dp[t ^ 1][y][cnt], dp[t][x][y] + baseDelta);
          }
          lastV1 = lastV2;
        } else {
          // DEBUGV("c");
          FOR(x, 0, MAXN) FORIF(y, 0, MAXN, dp[t][x][y] >= 0) {
            MMAX(dp[t ^ 1][0][cnt], dp[t][x][y] + baseDelta);
          }
          lastV1 = tiles[i] - 2;
        }
        lastV2 = tiles[i];
        cnt = 1;
        t ^= 1;
        FOR(x, 0, MAXN) {
          for (int y = MAXN - 1; y >= 3; --y) {
            if (dp[t][x][y] >= 0) {
              MMAX(dp[t][x][y - 3], dp[t][x][y] + 1);
            }
          }
        }
        // FOR(x, 0, MAXN) FORIF(y, 0, MAXN, dp[t][x][y] >= 0) {
        //   DEBUGVS(t, x, y, dp[t][x][y]);
        // }
      } else {
        ++cnt;
      }
    }
    int res = 0;
    FOR(x, 0, MAXN) {
      MMAX(res, *max_element(dp[t][x], dp[t][x] + MAXN));
    }
    return res;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
