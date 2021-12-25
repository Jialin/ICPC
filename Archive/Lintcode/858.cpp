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
#define FUNCTION_NAME candyCrush
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<vector<int>>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
[[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]
[[1,3,5,5,2],[3,4,3,3,1],[3,2,4,5,2],[2,4,4,5,5],[1,4,4,1,1]]
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
  vector<vector<int>> candyCrush(vector<vector<int>>& board) {
    int n = board.size(), m = board[0].size();
    while (true) {
      FOR(i, 0, n) FORIF(j, 0, m, board[i][j]) {
        if (i >= 2 && abs(board[i][j]) == abs(board[i - 1][j]) &&
            abs(board[i][j]) == abs(board[i - 2][j])) {
          board[i][j] = -abs(board[i][j]);
          board[i - 1][j] = -abs(board[i - 1][j]);
          board[i - 2][j] = -abs(board[i - 2][j]);
        }
        if (j >= 2 && abs(board[i][j]) == abs(board[i][j - 1]) &&
            abs(board[i][j]) == abs(board[i][j - 2])) {
          board[i][j] = -abs(board[i][j]);
          board[i][j - 1] = -abs(board[i][j - 1]);
          board[i][j - 2] = -abs(board[i][j - 2]);
        }
      }
      bool anyChange = false;
      FOR(i, 0, n) FORIF(j, 0, m, board[i][j] < 0) {
        anyChange = true;
        board[i][j] = 0;
      }
      if (!anyChange) {
        break;
      }
      FOR(j, 0, m) {
        int pnt = n - 1;
        FORR(i, n - 1, 0) {
          if (board[i][j]) {
            swap(board[pnt--][j], board[i][j]);
          }
        }
      }
    }
    return board;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
