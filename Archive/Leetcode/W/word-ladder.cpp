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
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    int n = beginWord.size();
    if (endWord.size() != n) {
      return 0;
    }
    unordered_set<string> words;
    for (auto& word : wordList) {
      words.insert(move(word));
    }
    if (!words.count(endWord)) {
      return 0;
    }
    queue<pair<string, int>> q;
    unordered_map<string, int> results;
    auto updater = [&](const string& word, int v) {
      if (!words.count(word)) {
        return;
      }
      if (results.count(word)) {
        return;
      }
      q.push({word, v});
      results[word] = v;
    };

    q.push({beginWord, 1});
    results[beginWord] = 1;
    for (; !q.empty(); q.pop()) {
      auto& pp = q.front();
      FOR(i, 0, n) {
        char c = pp.first[i];
        for (char newC = 'a'; newC <= 'z'; ++newC) {
          pp.first[i] = newC;
          updater(pp.first, pp.second + 1);
        }
        pp.first[i] = c;
      }
    }
    return results[endWord];
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseVector<string>("[\"hot\",\"dot\",\"dog\",\"lot\",\"log\",\"cog\"]");
    auto res = Solution().ladderLength("hit", "cog", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"hot\",\"dot\",\"dog\",\"lot\",\"log\"]");
    auto res = Solution().ladderLength("hit", "cog", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>(
        "[\"si\",\"go\",\"se\",\"cm\",\"so\",\"ph\",\"mt\",\"db\",\"mb\",\"sb\",\"kr\",\"ln\","
        "\"tm\",\"le\",\"av\",\"sm\",\"ar\",\"ci\",\"ca\",\"br\",\"ti\",\"ba\",\"to\",\"ra\","
        "\"fa\",\"yo\",\"ow\",\"sn\",\"ya\",\"cr\",\"po\",\"fe\",\"ho\",\"ma\",\"re\",\"or\","
        "\"rn\",\"au\",\"ur\",\"rh\",\"sr\",\"tc\",\"lt\",\"lo\",\"as\",\"fr\",\"nb\",\"yb\","
        "\"if\",\"pb\",\"ge\",\"th\",\"pm\",\"rb\",\"sh\",\"co\",\"ga\",\"li\",\"ha\",\"hz\","
        "\"no\",\"bi\",\"di\",\"hi\",\"qa\",\"pi\",\"os\",\"uh\",\"wm\",\"an\",\"me\",\"mo\","
        "\"na\",\"la\",\"st\",\"er\",\"sc\",\"ne\",\"mn\",\"mi\",\"am\",\"ex\",\"pt\",\"io\","
        "\"be\",\"fm\",\"ta\",\"tb\",\"ni\",\"mr\",\"pa\",\"he\",\"lr\",\"sq\",\"ye\"]");
    auto res = Solution().ladderLength("qa", "sq", v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
