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
  int scheduleCourse(vector<vector<int>>& courses) {
    sort(ALL(courses), [](const auto& x, const auto& y) {
      return x[1] < y[1];
    });
    priority_queue<int> costs;
    int totalCost = 0, res = 0;
    for (const auto& course : courses) {
      int cost = course[0];
      int end = course[1];
      if (totalCost + cost <= end) {
        costs.push(cost);
        totalCost += cost;
        ++res;
      } else if (!costs.empty() && costs.top() > cost && totalCost - costs.top() + cost <= end) {
        totalCost -= costs.top() - cost;
        costs.pop();
        costs.push(cost);
      }
    }
    return res;
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
    auto v1 =
        leetcode::parseVector<vector<int>>("[[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]");
    auto res = Solution().scheduleCourse(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[1,2]]");
    auto res = Solution().scheduleCourse(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<int>>("[[3,2],[4,3]]");
    auto res = Solution().scheduleCourse(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
