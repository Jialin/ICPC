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
#define FUNCTION_NAME strongPasswordChecker
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"aA1"
"1337C0d3"
"aaa123"
"a"
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
  int strongPasswordChecker(string password) {
    int n = password.size();

    auto calcTypeCnt = [&]() {
      bool digit = false, lower = false, upper = false;
      for (auto c : password) {
        if (isdigit(c)) {
          digit = true;
        } else if (islower(c)) {
          lower = true;
        } else if (isupper(c)) {
          upper = true;
        }
      }
      return !digit + 0 + !lower + !upper;
    };

    auto replaceCnt = [&]() {
      int cnt = 1, res = 0;
      FOR(i, 0, n) {
        if (i < n - 1 && password[i] == password[i + 1]) {
          ++cnt;
          continue;
        }
        res += cnt / 3;
        cnt = 1;
      }
      return res;
    };

    auto insertCnt = [&]() {
      return max(6 - n, 0);
    };

    auto replaceCntWithRemove = [&]() {
      int cnt = 1, replaceCnt = 0;
      int zeroCnt = 0, oneCnt = 0, twoCnt = 0;
      FOR(i, 0, n) {
        if (i < n - 1 && password[i] == password[i + 1]) {
          ++cnt;
          continue;
        }
        replaceCnt += cnt / 3;
        if (cnt >= 3) {
          if (cnt % 3 == 0) {
            ++zeroCnt;
          } else if (cnt % 3 == 1) {
            ++oneCnt;
          } else {
            ++twoCnt;
          }
        }
        cnt = 1;
      }
      int m = n;
      // zeroCnt
      int deltaReplaceCnt = min(zeroCnt, m - 20);
      m -= deltaReplaceCnt;
      replaceCnt -= deltaReplaceCnt;
      // oneCnt
      deltaReplaceCnt = min(oneCnt << 1, m - 20) >> 1;
      m -= deltaReplaceCnt << 1;
      replaceCnt -= deltaReplaceCnt;
      // twoCnt
      replaceCnt -= (m - 20) / 3;
      return replaceCnt;
    };

    if (n <= 20) {
      return max(max(calcTypeCnt(), replaceCnt()), insertCnt());
    } else {
      return n - 20 + max(calcTypeCnt(), replaceCntWithRemove());
    }
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
