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
#define FUNCTION_NAME secondMinimum
#define ARGUMENT_CNT 4
#define RETURN_VOID false
#define ARGUMENT_T_1 int
#define ARGUMENT_T_2 vector<vector<int>>
#define ARGUMENT_T_3 int
#define ARGUMENT_T_4 int
#define ARGUMENT_T_5 Interval

const string tests = R"(
5
[[1,2],[1,3],[1,4],[3,4],[4,5]]
3
5
2
[[1,2]]
3
2
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

const int INF = 1000000000;

class Solution {
public:
  int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
    vector<vector<int>> graph(n);
    for (auto& edge : edges) {
      graph[edge[0] - 1].push_back(edge[1] - 1);
      graph[edge[1] - 1].push_back(edge[0] - 1);
    }

    vector<int> minCost, minCost2;
    minCost.assign(n, INF);
    minCost2.assign(n, INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    auto updater = [&](int idx, int v) {
      if (minCost[idx] > v) {
        minCost2[idx] = minCost[idx];
        minCost[idx] = v;
        heap.push({v, idx});
      } else if (minCost[idx] < v && v < minCost2[idx]) {
        minCost2[idx] = v;
        heap.push({v, idx});
      }
    };
    updater(0, 0);
    while (!heap.empty()) {
      int v = heap.top().first, idx = heap.top().second;
      heap.pop();
      if (v > minCost2[idx]) {
        continue;
      }
      if (v % (change << 1) >= change) {
        v = (v / (change << 1) + 1) * (change << 1);
      }
      for (int newIdx : graph[idx]) {
        updater(newIdx, v + time);
      }
    }
    return minCost2[n - 1];
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
