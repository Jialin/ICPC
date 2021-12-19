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
  int findJudge(int n, vector<vector<int>>& trust) {
    vector<int> inCnt(n), outCnt(n);
    for (auto& edge : trust) {
      ++outCnt[edge[0] - 1];
      ++inCnt[edge[1] - 1];
    }
    int res = -1;
    FOR(i, 0, n) {
      if (!outCnt[i] && inCnt[i] == n - 1) {
        if (res < 0) {
          res = i + 1;
        } else {
          return -1;
        }
      }
    }
    return res;
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
    auto v1 = leetcode::parseVector<vector<int>>("[[1,2]]");
    auto res = Solution().findJudge(2, v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[1,3],[2,3]]");
    auto res = Solution().findJudge(3, v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[1,3],[2,3],[3,1]]");
    auto res = Solution().findJudge(3, v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[1,2],[2,3]]");
    auto res = Solution().findJudge(3, v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[1,3],[1,4],[2,3],[2,4],[4,3]]");
    auto res = Solution().findJudge(4, v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
