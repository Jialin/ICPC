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
  int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> rowMax(n);
    vector<int> colMax(m);
    FOR(i, 0, n) {
      FOR(j, 0, m) {
        rowMax[i] = max(rowMax[i], grid[i][j]);
        colMax[j] = max(colMax[j], grid[i][j]);
      }
    }
    int res = 0;
    FOR(i, 0, n) {
      FOR(j, 0, m) {
        res += min(rowMax[i], colMax[j]) - grid[i][j];
      }
    }
    return res;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]");
    auto res = Solution().maxIncreaseKeepingSkyline(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
