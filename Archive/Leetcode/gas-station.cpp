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
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    if (accumulate(ALL(gas), 0) < accumulate(ALL(cost), 0)) {
      return -1;
    }
    int n = gas.size();
    FOR(i, 0, n) {
      gas[i] -= cost[i];
    }
    vector<int> idxs;
    idxs.push_back(0);
    int m = 1;
    FOR(i, 1, n) {
      if (gas[i] >= 0 && gas[m - 1] >= 0) {
        gas[m - 1] += gas[i];
      } else if (gas[i] <= 0 && gas[m - 1] <= 0) {
        gas[m - 1] += gas[i];
      } else {
        gas[m++] = gas[i];
        idxs.push_back(i);
      }
    }
    FOR(i, 0, m) {
      int pnt = i, res = 0;
      bool valid = true;
      FOR(j, 0, m) {
        res += gas[pnt];
        if (res < 0) {
          valid = false;
          break;
        }
        pnt = pnt + 1 == m ? 0 : pnt + 1;
      }
      if (valid) {
        return idxs[i];
      }
    }
    return -1;
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
    auto v1 = leetcode::parseVector<int>("[1,2,3,4,5]");
    auto v2 = leetcode::parseVector<int>("[3,4,5,1,2]");
    auto res = Solution().canCompleteCircuit(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[2,3,4]");
    auto v2 = leetcode::parseVector<int>("[3,4,3]");
    auto res = Solution().canCompleteCircuit(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
