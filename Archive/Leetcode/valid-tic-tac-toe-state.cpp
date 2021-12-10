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
  bool validTicTacToe(vector<string>& board) {
    int xCnt = 0, oCnt = 0;
    FOR(i, 0, 3) FOR(j, 0, 3) {
      xCnt += board[i][j] == 'X';
      oCnt += board[i][j] == 'O';
    }
    auto isWin = [&](char c) {
      for (int i = 0; i < 3; ++i) {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c) {
          return true;
        }
        if (board[0][i] == c && board[1][i] == c && board[2][i] == c) {
          return true;
        }
      }
      if (board[0][0] == c && board[1][1] == c && board[2][2] == c) {
        return true;
      }
      return board[0][2] == c && board[1][1] == c && board[2][0] == c;
    };

    bool xWin = isWin('X');
    bool oWin = isWin('O');
    if (xWin && oWin) {
      return false;
    }
    if (xWin) {
      return xCnt == oCnt + 1;
    }
    if (oWin) {
      return xCnt == oCnt;
    }
    return xCnt == oCnt || xCnt == oCnt + 1;
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
    auto v1 = leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
    auto res = Solution().validTicTacToe(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"XOX\", \" X \", \"   \"]");
    auto res = Solution().validTicTacToe(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"XXX\", \"   \", \"OOO\"]");
    auto res = Solution().validTicTacToe(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"XOX\", \"O O\", \"XOX\"]");
    auto res = Solution().validTicTacToe(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<string>("[\"XXX\",\"XOO\",\"OO \"]");
    auto res = Solution().validTicTacToe(v1);
    cout << "=================================================================\n";
    DEBUGV(res);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
