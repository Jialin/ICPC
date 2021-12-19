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
  int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    auto minCost = [&](int lower, int upper) {
      if (fruits[upper - 1][0] <= startPos) {
        return startPos - fruits[lower][0];
      }
      if (startPos <= fruits[lower][0]) {
        return fruits[upper - 1][0] - startPos;
      }
      return min(startPos - fruits[lower][0], fruits[upper - 1][0] - startPos) +
             fruits[upper - 1][0] - fruits[lower][0];
    };
    int n = fruits.size();
    vector<int> psum(n + 1);
    FOR(i, 0, n) {
      psum[i + 1] = psum[i] + fruits[i][1];
    }
    int res = 0;
    FOR(i, 0, n) {
      int lower = i + 1, upper = n + 1;
      while (lower < upper) {
        int medium = (lower + upper) >> 1;
        if (minCost(i, medium) > k) {
          upper = medium;
        } else {
          lower = medium + 1;
          res = max(res, psum[medium] - psum[i]);
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
    auto v1 = leetcode::parseVector<vector<int>>("[[2,8],[6,3],[8,6]]");
    auto res = Solution().maxTotalFruits(v1, 5, 4);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]]");
    auto res = Solution().maxTotalFruits(v1, 5, 4);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[0,3],[6,4],[8,5]]");
    auto res = Solution().maxTotalFruits(v1, 3, 2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[200000,10000]]");
    auto res = Solution().maxTotalFruits(v1, 200000, 200000);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
