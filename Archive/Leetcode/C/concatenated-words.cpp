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
#define FUNCTION_NAME findAllConcatenatedWordsInADict
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<string>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
["cat","dog","catdog"]
["aaa","aaaa","aaaaa","aaaaaa"]
[""]
)";
#endif

#include "leetcode/linked_list_macros.h"

#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

template<int MAXL>
class Trie {
  int letterCnt;
  vector<int> children[MAXL];

  inline int createNode() {
    for (int i = 0; i < letterCnt; ++i)
      children[i].push_back(-1);
    return nodeCnt++;
  }

public:
  static const int ROOT = 0;
  int nodeCnt;

  // Initializes the trie with letter count
  inline void init(int _letterCnt) {
    letterCnt = _letterCnt;
    for (int i = 0; i < letterCnt; ++i)
      children[i].clear();
    nodeCnt = 0;
    createNode();
  }

  // Accesses the child and creates node when necessary
  inline int forceAccess(int idx, int letter) {
    int res = children[letter][idx];
    if (res < 0)
      res = createNode();
    return children[letter][idx] = res;
  }

  // Accesses the child
  inline int access(int idx, int letter) {
    return children[letter][idx];
  }
};

class Solution {
public:
  vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
    vector<bool> tags(100000 + 1);
    Trie<26> trie;
    trie.init(26);
    sort(words.begin(), words.end(), [](const auto& x, const auto& y) {
      return x.size() < y.size();
    });
    vector<string> results;
    for (const auto& word : words) {
      vector<int> bfs;
      bfs.push_back(0);
      vector<int> nxtBfs;
      for (char c : word) {
        nxtBfs.clear();
        bool restart = false;
        for (int idx : bfs) {
          int nxtIdx = trie.access(idx, c - 'a');
          if (nxtIdx < 0) {
            continue;
          }
          nxtBfs.push_back(nxtIdx);
          if (tags[nxtIdx]) {
            restart = true;
          }
        }
        if (restart) {
          nxtBfs.push_back(0);
        }
        swap(bfs, nxtBfs);
      }
      if (!word.empty() && find(ALL(bfs), 0) != bfs.end()) {
        results.push_back(word);
      } else {
        int u = 0;
        for (char c : word) {
          u = trie.forceAccess(u, c - 'a');
        }
        tags[u] = true;
      }
    }
    return results;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
