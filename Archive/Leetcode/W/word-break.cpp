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
  bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> words;
    for (string& s : wordDict) {
      words.insert(move(s));
    }
    int n = s.size();
    vector<bool> visited(n + 1);
    queue<int> q;

    visited[0] = true;
    q.push(0);
    for (; !q.empty(); q.pop()) {
      int idx = q.front();
      // DEBUGV(idx);
      FOR(i, idx + 1, n + 1) {
        if (!visited[i] && words.count(s.substr(idx, i - idx))) {
          // DEBUGF("%d->%d %s\n", idx, i, s.substr(idx, i - idx).c_str());
          visited[i] = true;
          q.push(i);
        }
      }
    }
    return visited[n];
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
    auto v1 = leetcode::parseVector<string>("[\"leet\", \"code\"]");
    auto res = Solution().wordBreak("leetcode", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"apple\", \"pen\"]");
    auto res = Solution().wordBreak("applepenapple", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"cats\", \"dog\", \"sand\", \"and\", \"cat\"]");
    auto res = Solution().wordBreak("catsandog", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
