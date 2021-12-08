// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "leetcode/parse.h"

// Last include
#include "debug/debug.h"

class Solution {
public:
  vector<int> findEvenNumbers(vector<int>& digits) {
    unordered_map<int, int> cnts;
    for (int digit : digits) {
      ++cnts[digit];
    }
    vector<int> res;
    for (int n = 100; n < 1000; n += 2) {
      --cnts[n / 100];
      --cnts[n / 10 % 10];
      --cnts[n % 10];
      bool valid = true;
      for (auto [k, v] : cnts) {
        if (v < 0) {
          valid = false;
          break;
        }
      }
      if (valid) {
        res.push_back(n);
      }
      ++cnts[n / 100];
      ++cnts[n / 10 % 10];
      ++cnts[n % 10];
    }
    return res;
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  {
    auto v1 = leetcode::parseVector<int>("[2,1,3,0]");
    auto res = Solution().findEvenNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[2,2,8,8,2]");
    auto res = Solution().findEvenNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[3,7,5]");
    auto res = Solution().findEvenNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[0,2,0,0]");
    auto res = Solution().findEvenNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<int>("[0,0,0]");
    auto res = Solution().findEvenNumbers(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
