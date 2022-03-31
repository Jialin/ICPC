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
#define FUNCTION_NAME pacificAtlantic
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<int>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
[[2,1],[1,2]]
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
  vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int n = heights.size();
    int m = heights.front().size();
    vector<vector<bool>> lTags(n, vector<bool>(m));
    vector<vector<bool>> rTags(n, vector<bool>(m));
    queue<pair<int, int>> q;

    auto update = [&](int x, int y, int bound, vector<vector<bool>>& tags) {
      if (x < 0 || x >= n || y < 0 || y >= m || tags[x][y] || heights[x][y] < bound) {
        return;
      }
      tags[x][y] = true;
      q.emplace(x, y);
    };

    auto bfs = [&](vector<vector<bool>>& tags) {
      while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front();
        q.pop();
        int h = heights[x][y];
        update(x - 1, y, h, tags);
        update(x + 1, y, h, tags);
        update(x, y - 1, h, tags);
        update(x, y + 1, h, tags);
      }
    };

    // left
    for (int i = 0; i < n; ++i) {
      update(i, 0, 0, lTags);
    }
    for (int j = 1; j < m; ++j) {
      update(0, j, 0, lTags);
    }
    bfs(lTags);
    // right
    for (int i = 0; i < n; ++i) {
      update(i, m - 1, 0, rTags);
    }
    for (int j = 0; j < m - 1; ++j) {
      update(n - 1, j, 0, rTags);
    }
    bfs(rTags);

    vector<vector<int>> res;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (lTags[i][j] && rTags[i][j]) {
          res.push_back({i, j});
        }
      }
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
