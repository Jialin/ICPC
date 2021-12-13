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
  string expressionExpand(string& s) {
    int n = s.size();
    vector<stringstream> sss;
    sss.emplace_back();
    vector<int> duplicates;
    for (int i = 0; i < n; ++i) {
      if (isdigit(s[i])) {
        duplicates.push_back(0);
        for (; i < n && isdigit(s[i]); duplicates.back() = duplicates.back() * 10 + s[i++] - '0') {}
        sss.emplace_back();
      } else if (s[i] == ']') {
        string subS = sss.back().str();
        sss.pop_back();
        FOR(i, 0, duplicates.back()) {
          sss.back() << subS;
        }
        duplicates.pop_back();
      } else {
        sss.back() << s[i];
      }
    }
    return sss.back().str();
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<Interval>("[(1,3),(2,6),(8,10),(15,18)]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    string v1 = "abc3[a]";
    auto res = Solution().expressionExpand(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    string v1 = "3[2[ad]3[pf]]xyz";
    auto res = Solution().expressionExpand(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    string v1 = "10[xyz]";
    auto res = Solution().expressionExpand(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
