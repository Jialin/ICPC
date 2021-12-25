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
#define FUNCTION_NAME evalRPN
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<string>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
["2","1","+","3","*"]
["4","13","5","/","+"]
["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
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
  int evalRPN(vector<string>& tokens) {
    vector<int> st;
    for (const auto& token : tokens) {
      if (token.size() == 1 && !isdigit(token[0])) {
        int x = st.back();
        st.pop_back();
        int y = st.back();
        st.pop_back();
        int res;
        if (token[0] == '+') {
          res = x + y;
        } else if (token[0] == '-') {
          res = y - x;
        } else if (token[0] == '*') {
          res = x * y;
        } else if (token[0] == '/') {
          res = y / x;
        }
        st.push_back(res);
      } else {
        st.push_back(atoi(token.data()));
      }
    }
    return st.back();
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
