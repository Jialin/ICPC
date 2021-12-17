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
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    unordered_map<string, int> words;
    FORSIZE(i, wordDict) {
      words[wordDict[i]] = i;
    }
    int n = s.size();
    vector<bool> visited(n + 1);
    vector<vector<int>> graph(n);
    queue<int> q;
    visited[0] = true;
    q.push(0);
    for (; !q.empty(); q.pop()) {
      int startIdx = q.front();
      FOR(endIdx, startIdx + 1, n + 1) {
        const auto it = words.find(s.substr(startIdx, endIdx - startIdx));
        if (it == words.end()) {
          continue;
        }
        graph[startIdx].push_back(it->second);
        if (!visited[endIdx]) {
          visited[endIdx] = true;
          q.push(endIdx);
        }
      }
    }
    if (!visited[n]) {
      return {};
    }
    vector<bool> reachable(n + 1);
    reachable[n] = true;
    for (int i = n - 1; i >= 0; --i) {
      for (int wordIdx : graph[i]) {
        // DEBUGF("%d -> %s\n", i, wordDict[wordIdx].c_str());
        if (reachable[i + wordDict[wordIdx].size()]) {
          reachable[i] = true;
          break;
        }
      }
    }
    // DEBUGV(reachable);

    vector<string> res;
    vector<string> subRes;
    function<void(int)> dfs;
    dfs = [&](int startIdx) {
      if (!reachable[startIdx]) {
        return;
      }
      if (startIdx == n) {
        stringstream ss;
        ss << subRes.front();
        FOR(i, 1, SIZE(subRes)) {
          ss << ' ' << subRes[i];
        }
        res.push_back(ss.str());
        return;
      }
      for (int wordIdx : graph[startIdx]) {
        subRes.push_back(wordDict[wordIdx]);
        dfs(startIdx + wordDict[wordIdx].size());
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
    auto v1 = leetcode::parseVector<string>("[\"cat\", \"cats\", \"and\", \"sand\", \"dog\"]");
    auto res = Solution().wordBreak("catsanddog", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>(
        "[\"apple\", \"pen\", \"applepen\", \"pine\", \"pineapple\"]");
    auto res = Solution().wordBreak("pineapplepenapple", v1);
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
