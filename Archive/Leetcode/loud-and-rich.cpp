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
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    int n = quiet.size();
    unordered_map<int, vector<int>> graph;
    vector<int> inDegrees(n);
    for (auto& rich : richer) {
      graph[rich[0]].push_back(rich[1]);
      ++inDegrees[rich[1]];
    }
    vector<int> results(n);
    FOR(i, 0, n) {
      results[i] = i;
    }
    queue<int> q;
    FOR(i, 0, n) {
      if (!inDegrees[i]) {
        q.push(i);
      }
    }
    for (; !q.empty(); q.pop()) {
      int u = q.front();
      for (int v : graph[u]) {
        if (quiet[results[u]] < quiet[results[v]]) {
          results[v] = results[u];
        }
        --inDegrees[v];
        if (!inDegrees[v]) {
          q.push(v);
        }
      }
    }
    return results;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<Interval>("[(1,3),(2,6),(8,10),(15,18)]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]]");
    auto v2 = leetcode::parseVector<int>("[3,2,5,4,6,1,7,0]");
    auto res = Solution().loudAndRich(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[]");
    auto v2 = leetcode::parseVector<int>("[0]");
    auto res = Solution().loudAndRich(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
