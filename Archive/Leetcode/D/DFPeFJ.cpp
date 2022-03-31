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
#define FUNCTION_NAME electricCarPlan
#define ARGUMENT_CNT 5
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<int>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 int
#define ARGUMENT_T_4 int
#define ARGUMENT_T_5 vector<int>

const string tests = R"(
[[1,3,3],[3,2,1],[2,1,3],[0,1,4],[3,0,5]]
6
1
0
[2,10,4,1]
[[0,4,2],[4,3,5],[3,0,5],[0,1,5],[3,2,4],[1,2,8]]
8
0
2
[4,1,1,3,2]
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
  int electricCarPlan(
      vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charges) {
    int n = charges.size();
    vector<vector<pair<int, int>>> graph(n);
    for (const auto& path : paths) {
      int x = path[0], y = path[1], v = path[2];
      graph[x].emplace_back(y, v);
      graph[y].emplace_back(x, v);
    }

    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>>
        heap;
    vector<vector<int>> memo(n, vector<int>(cnt + 1, -1));
    auto update = [&](int u, int oil, int subRes) {
      auto& res = memo[u][oil];
      if (res < 0 || res > subRes) {
        res = subRes;
        heap.emplace(res, u, oil);
      }
    };

    update(start, 0, 0);
    while (!heap.empty()) {
      int cost, u, oil;
      tie(cost, u, oil) = heap.top();
      heap.pop();
      if (u == end) {
        return cost;
      }
      if (cost != memo[u][oil]) {
        continue;
      }
      if (oil < cnt) {
        update(u, oil + 1, cost + charges[u]);
      }
      for (const auto& path : graph[u]) {
        int v, deltaOil;
        tie(v, deltaOil) = path;
        if (oil >= deltaOil) {
          update(v, oil - deltaOil, cost + deltaOil);
        }
      }
    }
    return -1;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
