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
  vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    int n = SIZE(nums);
    vector<int> psum(n + 1);
    FOR(i, 0, n) {
      psum[i + 1] = psum[i] + nums[i];
    }

    int subBest = 0;

    vector<int> dp1(n - k + 1);
    for (int i = n - k; i >= 0; --i) {
      dp1[i] = psum[i + k] - psum[i];
    }

    vector<int> dp2(n - (k << 1) + 1);
    subBest = dp1[n - k];
    for (int i = n - (k << 1); i >= 0; --i) {
      subBest = max(subBest, dp1[i + k]);
      dp2[i] = psum[i + k] - psum[i] + subBest;
    }

    vector<int> dp3(n - k * 3 + 1);
    subBest = dp2[n - (k << 1)];
    for (int i = n - k * 3; i >= 0; --i) {
      subBest = max(subBest, dp2[i + k]);
      dp3[i] = psum[i + k] - psum[i] + subBest;
    }

    int idx3 = max_element(ALL(dp3)) - dp3.begin();
    int idx2 = max_element(dp2.begin() + idx3 + k, dp2.end()) - dp2.begin();
    int idx1 = max_element(dp1.begin() + idx2 + k, dp1.end()) - dp1.begin();
    return {idx3, idx2, idx1};
  }
};

#ifdef LOCAL

int main() {
  {
    auto v1 = leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
    auto v2 = 2;
    auto res = Solution().maxSumOfThreeSubarrays(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
