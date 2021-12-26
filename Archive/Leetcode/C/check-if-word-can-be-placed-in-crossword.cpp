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
#define FUNCTION_NAME placeWordInCrossword
#define ARGUMENT_CNT 2
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<char>>
#define ARGUMENT_T_2 string
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]]
"abc"
[[" ", "#", "a"], [" ", "#", "c"], [" ", "#", "a"]]
"ac"
[["#", " ", "#"], [" ", " ", "#"], ["#", " ", "c"]]
"ca"
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
  bool placeWordInCrossword(vector<vector<char>>& board, string word) {
    int n = board.size(), m = board[0].size();
    int len = word.size();

    auto validRow = [&](int x, int y) {
      bool valid = true;
      FOR(i, 0, len) {
        if (board[x][y + i] != ' ' && board[x][y + i] != word[i]) {
          valid = false;
          break;
        }
      }
      if (valid) {
        return true;
      }
      valid = true;
      FOR(i, 0, len) {
        if (board[x][y + i] != ' ' && board[x][y + i] != word[len - 1 - i]) {
          valid = false;
          break;
        }
      }
      return valid;
    };

    auto validCol = [&](int x, int y) {
      bool valid = true;
      FOR(i, 0, len) {
        if (board[x + i][y] != ' ' && board[x + i][y] != word[i]) {
          valid = false;
          break;
        }
      }
      if (valid) {
        return true;
      }
      valid = true;
      FOR(i, 0, len) {
        if (board[x + i][y] != ' ' && board[x + i][y] != word[len - 1 - i]) {
          valid = false;
          break;
        }
      }
      return valid;
    };

    FOR(i, 0, n) {
      int lastJ = 0;
      FOR(j, 0, m) {
        if (board[i][j] == '#') {
          if (j - lastJ == len && validRow(i, lastJ)) {
            return true;
          }
          lastJ = j + 1;
        }
      }
      if (m - lastJ == len && validRow(i, lastJ)) {
        return true;
      }
    }
    FOR(j, 0, m) {
      int lastI = 0;
      FOR(i, 0, n) {
        if (board[i][j] == '#') {
          if (i - lastI == len && validCol(lastI, j)) {
            return true;
          }
          lastI = i + 1;
        }
      }
      if (n - lastI == len && validCol(lastI, j)) {
        return true;
      }
    }
    return false;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
