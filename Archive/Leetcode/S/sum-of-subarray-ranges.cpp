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
  long long subArrayRanges(vector<int>& nums) {
    int n = nums.size();
    int64_t res = 0;
    FOR(i, 0, n) {
      int minV = nums[i], maxV = nums[i];
      FOR(j, i + 1, n) {
        MMIN(minV, nums[j]);
        MMAX(maxV, nums[j]);
        res += maxV - minV;
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
    auto v1 = leetcode::parseVector<int>("[1,2,3]");
    auto res = Solution().subArrayRanges(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[1,3,3]");
    auto res = Solution().subArrayRanges(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[4,-2,-3,4,1]");
    auto res = Solution().subArrayRanges(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
