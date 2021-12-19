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
  int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
    int pntA = 0, pntB = plants.size() - 1;
    int remA = capacityA, remB = capacityB;
    int res = 0;

    auto checker = [&](int& rem, int cap, int plant) {
      if (rem < plant) {
        ++res;
        rem = cap;
      }
      rem -= plant;
    };

    for (; pntA <= pntB; ++pntA, --pntB) {
      if (pntA == pntB) {
        if (remA >= remB) {
          checker(remA, capacityA, plants[pntA]);
        } else {
          checker(remB, capacityB, plants[pntB]);
        }
      } else {
        checker(remA, capacityA, plants[pntA]);
        checker(remB, capacityB, plants[pntB]);
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
    auto v1 = leetcode::parseVector<int>("[2,2,3,3]");
    auto res = Solution().minimumRefill(v1, 5, 5);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[2,2,3,3]");
    auto res = Solution().minimumRefill(v1, 3, 4);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[5]");
    auto res = Solution().minimumRefill(v1, 10, 8);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[1,2,4,4,5]");
    auto res = Solution().minimumRefill(v1, 6, 5);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[2,2,5,2,2]");
    auto res = Solution().minimumRefill(v1, 5, 5);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
