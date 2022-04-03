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
#define FUNCTION_NAME kthPalindrome
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[1,2,3,4,5,90]
3
[2,4,6]
4
[35]
6
[41]
4
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

const int POW10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int64_t calc(int idx, int len) {
  if (len == 1) {
    return idx >= 9 ? -1 : idx + 1;
  }
  int64_t totalCnt = POW10[(len >> 1) - 1] * 9LL;
  if (len & 1) {
    totalCnt *= 10;
  }
  if (idx >= totalCnt) {
    return -1;
  }
  stringstream ss;
  int actualIdx = (len & 1) ? idx / 10 : idx;
  string subRes = to_string(POW10[(len >> 1) - 1] + actualIdx);
  ss << subRes;
  if (len & 1) {
    ss << idx % 10;
  }
  reverse(ALL(subRes));
  ss << subRes;
  return atol(ss.str().c_str());
}

class Solution {
public:
  vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
    vector<long long> res;
    for (auto query : queries) {
      res.push_back(calc(query - 1, intLength));
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
