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
  int maxProfit(vector<int>& prices) {
    int n = SIZE(prices);
    int best;

    vector<int> forward(n);
    best = prices[0];
    FOR(i, 1, n) {
      forward[i] = max(forward[i - 1], prices[i] - best);
      best = min(best, prices[i]);
    }
    vector<int> backward(n + 1);
    best = prices[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      backward[i] = max(backward[i + 1], best - prices[i]);
      best = max(best, prices[i]);
    }
    int res = forward[n - 1];
    FOR(i, 1, n - 1) {
      res = max(res, forward[i] + backward[i + 1]);
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
    auto v1 = leetcode::parseVector<int>("[3,3,5,0,0,3,1,4]");
    auto res = Solution().maxProfit(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[1,2,3,4,5]");
    auto res = Solution().maxProfit(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[7,6,4,3,1]");
    auto res = Solution().maxProfit(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[1]");
    auto res = Solution().maxProfit(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
