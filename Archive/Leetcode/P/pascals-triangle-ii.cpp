// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#ifdef LOCAL
#include "leetcode/parse.h"
#endif

// Last include
#include "debug/debug.h"

class Solution {
public:
  vector<int> getRow(int n) {
    vector<int> res;
    res.push_back(1);
    FOR(i, 0, n) {
      res.push_back(CAST<int64_t>(res.back()) * (n - i) / (i + 1));
    }
    return res;
  }
};

#ifdef LOCAL

int main() {
  {
    auto res = Solution().getRow(3);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().getRow(0);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().getRow(1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().getRow(33);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
