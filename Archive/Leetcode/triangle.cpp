// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#ifdef LOCAL
#include "leetcode/parse.h"
#endif

// Last include
#include "debug/debug.h"

class Solution {
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    vector<vector<int>> dp = triangle;
    int n = triangle.size();
    for (int i = n - 2; i >= 0; --i) {
      for (int j = (0); j < (i + 1); ++j) {
        dp[i][j] += min(dp[i + 1][j], dp[i + 1][j + 1]);
      }
    }
    return dp[0][0];
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
    auto res = Solution().minimumTotal(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[-10]]");
    auto res = Solution().minimumTotal(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
