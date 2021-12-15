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
  vector<vector<string>> partition(string s) {
    int n = s.size();
    vector<vector<string>> res;
    vector<string> subRes;
    vector<vector<bool>> isValid(n, vector<bool>(n));
    FOR(i, 0, n) {
      int l, r;
      l = i + 1, r = i - 1;
      for (--l, ++r; 0 <= l && r < n && s[l] == s[r]; --l, ++r) {
        isValid[l][r] = true;
      }
      l = i + 1, r = i;
      for (--l, ++r; 0 <= l && r < n && s[l] == s[r]; --l, ++r) {
        isValid[l][r] = true;
      }
    }

    function<void(int)> dfs;
    dfs = [&](int idx) {
      if (idx == n) {
        res.push_back(subRes);
        return;
      }
      FORIF(i, idx, n, isValid[idx][i]) {
        subRes.push_back(s.substr(idx, i - idx + 1));
        dfs(i + 1);
        subRes.pop_back();
      }
    };
    dfs(0);

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
    auto res = Solution().partition("aab");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto res = Solution().partition("a");
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
