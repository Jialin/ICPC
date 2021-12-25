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
#define FUNCTION_NAME simplifyPath
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 string
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
"/home/"
"/a/./../../c/"
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
  string simplifyPath(string& path) {
    vector<string> vs;
    int last = 1;
    while (last < path.size()) {
      int nxtPos = find_if(
                       path.begin() + last,
                       path.end(),
                       [](char c) {
                         return c == '/';
                       }) -
                   path.begin();
      vs.push_back(path.substr(last, nxtPos - last));
      last = nxtPos + 1;
    }
    vector<string> st;
    for (auto& v : vs) {
      if (v.empty() || v == ".") {
        continue;
      }
      if (v == "..") {
        if (!st.empty()) {
          st.pop_back();
        }
        continue;
      }
      st.push_back(move(v));
    }
    if (st.empty()) {
      return "/";
    }
    stringstream ss;
    for (auto& v : st) {
      ss << '/' << move(v);
    }
    return ss.str();
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
