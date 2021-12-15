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
  void solve(vector<vector<char>>& board) {
    int n = board.size();
    int m = board[0].size();
    queue<pair<int, int>> q;

    auto updater = [&](int x, int y) {
      if (x < 0 || x >= n || y < 0 || y >= m || board[x][y] != 'O') {
        return;
      }
      board[x][y] = '.';
      q.push({x, y});
    };
    FOR(i, 0, n) {
      updater(i, 0);
      updater(i, m - 1);
    }
    FOR(j, 0, m) {
      updater(0, j);
      updater(n - 1, j);
    }
    for (; !q.empty(); q.pop()) {
      int x = q.front().first;
      int y = q.front().second;
      updater(x - 1, y);
      updater(x + 1, y);
      updater(x, y - 1);
      updater(x, y + 1);
    }

    FOR(i, 0, n) {
      FOR(j, 0, m) {
        board[i][j] = board[i][j] == '.' ? 'O' : 'X';
      }
    }
  }
};

#ifdef LOCAL

int main() {
  leetcode::parseVector<int>("[1,2,1,2,6,7,5,1]");
  leetcode::parseVector<string>("[\"O  \", \"   \", \"   \"]");
  leetcode::parseVector<Interval>("[(1,3),(2,6),(8,10),(15,18)]");
  leetcode::parseVector<vector<char>>(
      "[[\"X\",\"X\",\"X\",\"X\"],[\"X\",\"O\",\"O\",\"X\"],[\"X\",\"X\","
      "\"O\",\"X\"],[\"X\",\"O\",\"X\",\"X\"]]");
  leetcode::parseVector<vector<int>>("[[2],[3,4],[6,5,7],[4,1,8,3]]");
  leetcode::parseLinkedList("[1,3,4,7,1,2,6]");
  leetcode::parseBinaryTree("[5,1,2,3,null,6,4]");
  {
    auto v1 = leetcode::parseVector<vector<char>>(
        "[[\"X\",\"X\",\"X\",\"X\"],[\"X\",\"O\",\"O\",\"X\"],[\"X\",\"X\","
        "\"O\",\"X\"],[\"X\",\"O\",\"X\",\"X\"]]");
    Solution().solve(v1);
    cout << "=================================================================\n";
    DEBUGV(v1);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<char>>("[[\"X\"]]");
    Solution().solve(v1);
    cout << "=================================================================\n";
    DEBUGV(v1);
    cout << "=================================================================\n";
  }
  {
    auto v1 = leetcode::parseVector<vector<char>>("[[\"O\"]]");
    Solution().solve(v1);
    cout << "=================================================================\n";
    DEBUGV(v1);
    cout << "=================================================================\n";
  }
  return 0;
}
#endif
