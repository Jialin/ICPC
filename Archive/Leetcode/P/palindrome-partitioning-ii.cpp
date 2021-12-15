// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "leetcode/binary_tree_macros.h"
#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/linked_list.h"
#include "leetcode/parse.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  int minCut(string s) {
    int n = s.size();
    vector<int> dp(n + 1);
    dp[0] = 0;
    vector<int> poss;
    vector<int> newPoss;
    FOR(i, 0, n) {
      newPoss.clear();
      int& res = dp[i + 1];
      res = dp[i] + 1;
      newPoss.push_back(i);
      if (i && s[i - 1] == s[i]) {
        res = min(res, dp[i - 1] + 1);
        newPoss.push_back(i - 1);
      }
      for (int pos : poss) {
        if (pos && s[i] == s[pos - 1]) {
          newPoss.push_back(pos - 1);
          res = min(res, dp[pos - 1] + 1);
        }
      }
      swap(poss, newPoss);
    }
    // DEBUGV(dp);
    return dp.back() - 1;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<vector<char>>(
      "[[\"X\",\"X\",\"X\",\"X\"],[\"X\",\"O\",\"O\",\"X\"],[\"X\",\"X\","
      "\"O\",\"X\"],[\"X\",\"O\",\"X\",\"X\"]]");
  leetcode::parseVector<Interval>("[(1,3),(2,6),(8,10),(15,18)]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto res = Solution().minCut("aab");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().minCut("a");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().minCut("ab");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
