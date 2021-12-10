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
  string shortestCompletingWord(string licensePlate, vector<string>& words) {
    unordered_map<char, int> cnts;
    for (char c : licensePlate) {
      if (isalpha(c)) {
        ++cnts[tolower(c)];
      }
    }

    auto isValid = [&](string& word) {
      for (char c : word) {
        --cnts[c];
      }
      bool valid = true;
      for (auto [k, v] : cnts) {
        if (v > 0) {
          valid = false;
          break;
        }
      }
      for (char c : word) {
        ++cnts[c];
      }
      return valid;
    };
    int res = -1;
    FORSIZE(i, words) {
      if (isValid(words[i])) {
        if (res < 0 || words[res].size() > words[i].size()) {
          res = i;
        }
      }
    }
    return words[res];
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
    auto v1 = "1s3 PSt";
    auto v2 = leetcode::parseVector<string>("[\"step\", \"steps\", \"stripe\", \"stepple\"]");
    auto res = Solution().shortestCompletingWord(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = "1s3 456";
    auto v2 = leetcode::parseVector<string>("[\"looks\", \"pest\", \"stew\", \"show\"]");
    auto res = Solution().shortestCompletingWord(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = "Ah71752";
    auto v2 =
        leetcode::parseVector<string>("[\"suggest\",\"letter\",\"of\",\"husband\",\"easy\","
                                      "\"education\",\"drug\",\"prevent\",\"writer\",\"old\"]");
    auto res = Solution().shortestCompletingWord(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = "OgEu755";
    auto v2 = leetcode::parseVector<string>("[\"enough\",\"these\",\"play\",\"wide\",\"wonder\","
                                            "\"box\",\"arrive\",\"money\",\"tax\",\"thus\"]");
    auto res = Solution().shortestCompletingWord(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = "iMSlpe4";
    auto v2 =
        leetcode::parseVector<string>("[\"claim\",\"consumer\",\"student\",\"camera\",\"public\","
                                      "\"never\",\"wonder\",\"simple\",\"thought\",\"use\"]");
    auto res = Solution().shortestCompletingWord(v1, v2);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
