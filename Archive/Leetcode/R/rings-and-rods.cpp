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
  int countPoints(string rings) {
    vector<int> masks(10);
    for (int i = 0; i < rings.size(); i += 2) {
      char c = rings[i];
      int mask = 4;
      if (c == 'R') {
        mask = 1;
      } else if (c == 'G') {
        mask = 2;
      }
      masks[rings[i + 1] - '0'] |= mask;
    }
    return count(ALL(masks), 7);
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
    auto res = Solution().countPoints("B0B6G0R6R0R6G9");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().countPoints("B0R0G0R9R0B0G0");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().countPoints("G4");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
