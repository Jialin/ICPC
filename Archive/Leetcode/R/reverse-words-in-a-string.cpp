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
#define FUNCTION_NAME reverseWords
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"the sky is blue"
"  hello world  "
"a good   example"
"  Bob    Loves  Alice   "
"Alice does not even like bob"
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
  string reverseWords(string s) {
    istringstream iss(s);
    vector<string> vs;
    while (iss >> s) {
      vs.push_back(s);
    }
    stringstream oss;
    oss << vs.back();
    FORR(i, SIZE(vs) - 2, 0) {
      oss << ' ' << vs[i];
    }
    return oss.str();
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
