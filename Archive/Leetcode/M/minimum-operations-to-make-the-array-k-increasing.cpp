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
#define FUNCTION_NAME kIncreasing
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<int>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[5,4,3,2,1]
1
[4,1,5,2,6,2]
2
[4,1,5,2,6,2]
3
[12,6,12,6,14,2,13,17,3,8,11,7,4,11,18,8,8,3]
1
)";
#endif

#include "leetcode/binary_tree_macros.h"
#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

template<typename T>
class LIS {
public:
  inline void init(int n) {
    lis_.clear();
    lis_.reserve(n);
    result_ = 0;
  }

  inline int locateIdx(const T& v) const {
    return CAST<int>(
        lower_bound(
            lis_.begin(),
            lis_.end(),
            v,
            [](int x, int y) {
              return x <= y;
            }) -
        lis_.begin());
  }

  inline void add(const T& v) {
    int idx = locateIdx(v);
    if (idx == SIZE(lis_)) {
      lis_.push_back(v);
    } else {
      lis_[idx] = v;
    }
  }

  inline int length() const {
    return SIZE(lis_);
  }

public:
  vector<T> lis_;
  int result_;
}; // class LIS

class Solution {
public:
  int calc(vector<int>& vs) {
    int n = vs.size();
    LIS<int> lis;
    lis.init(n);
    for (int v : vs) {
      lis.add(v);
    }
    // DEBUGV(lis.lis_);
    return n - lis.length();
  }

  int kIncreasing(vector<int>& arr, int k) {
    int res = 0;
    FOR(i, 0, k) {
      vector<int> vs;
      for (int j = i; j < arr.size(); j += k) {
        vs.push_back(arr[j]);
      }
      res += calc(vs);
    }
    return res;
  }
};

#ifdef LOCAL
int main() {
  leetcode::handle<Solution>(tests);
  return 0;
}
#endif
