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
#define FUNCTION_NAME busiestServers
#define ARGUMENT_CNT 3
#define RETURN_VOID false
#define ARGUMENT_T_1 int
#define ARGUMENT_T_2 vector<int>
#define ARGUMENT_T_3 vector<int>
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
3
[1,2,3,4,5]
[5,2,3,3,3]
3
[1,2,3,4]
[1,2,1,2]
3
[1,2,3]
[10,12,11]
3
[1,2,3,4,8,9,10]
[5,2,10,3,1,2,2]
1
[1]
[1]
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
  vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
    set<int> servers;
    for (int i = 0; i < k; ++i) {
      servers.insert(i);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    vector<int> cnts(k);
    for (int i = 0, j = 0; i < arrival.size(); ++i, j = j == k - 1 ? 0 : j + 1) {
      for (; !heap.empty() && heap.top().first <= arrival[i]; heap.pop()) {
        servers.insert(heap.top().second);
      }
      const auto it = servers.lower_bound(j);
      if (it != servers.end()) {
        heap.emplace(arrival[i] + load[i], *it);
        ++cnts[*it];
        servers.erase(it);
      } else if (!servers.empty()) {
        heap.emplace(arrival[i] + load[i], *servers.begin());
        ++cnts[*servers.begin()];
        servers.erase(servers.begin());
      }
    }
    int resCnt = *max_element(ALL(cnts));
    vector<int> res;
    FORIF(i, 0, k, cnts[i] == resCnt) {
      res.push_back(i);
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
