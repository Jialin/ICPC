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
#define FUNCTION_NAME eatenApples
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 vector<int>
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,2,3,5,2]
[3,2,1,4,2]
[3,0,0,0,0,2]
[3,0,0,0,0,2]
[5,2,3]
[6,9,10]
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
  int eatenApples(vector<int>& apples, vector<int>& days) {
    map<int, int> remainCnts;
    int n = apples.size();
    int res = 0;
    FOR(i, 0, n) {
      if (apples[i]) {
        remainCnts[i + days[i] - 1] += apples[i];
      }
      if (remainCnts.empty()) {
        continue;
      }
      auto it = remainCnts.begin();
      ++res;
      --it->second;
      if (it->first == i || !it->second) {
        remainCnts.erase(it);
      }
    }
    int last = n;
    for (auto [key, value] : remainCnts) {
      int cnt = min(value, key - last + 1);
      res += cnt;
      last += cnt;
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
