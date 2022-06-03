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
#define FUNCTION_NAME guardCastle
#define ARGUMENT_CNT 1
#define RETURN_VOID false
#define ARGUMENT_T_1 vector<string>
#define ARGUMENT_T_2 int
#define ARGUMENT_T_3 ListNode*
#define ARGUMENT_T_4 TreeNode*
#define ARGUMENT_T_5 Interval

const string tests = R"(
["S.C.P#P.", ".....#.S"]
["SP#P..P#PC#.S", "..#P..P####.#"]
["SP#.C.#PS", "P.#...#.P"]
["CP.#.P.", "...S..S"]
)";
#endif

#define DINIC_FLOW

#include "graph/flow/dinic_macros.h"
#include "leetcode/linked_list_macros.h"

#include "graph/flow/dinic.h"
#include "leetcode/binary_tree.h"
#include "leetcode/handler.h"
#include "leetcode/linked_list.h"

// Last include
#include "debug/debug.h"

const int DX[4] = {1, -1, 0, 0};
const int DY[4] = {0, 0, 1, -1};

class Solution {
public:
  int guardCastle(vector<string>& grid) {
    graph::Dinic<int> dinic;
    int m = grid[0].size();
    int inf = m << 1;
    int source = -1;
    int sink = m << 2;
    int port = sink + 1;
    dinic.init(port + 1);
    int idx = 0;
    FOR(i, 0, 2) FOR(j, 0, m) {
      if (grid[i][j] == 'P') {
        dinic.addEdge((idx << 1) | 1, port, inf);
        dinic.addEdge(port, idx << 1, inf);
      } else if (grid[i][j] == 'S') {
        dinic.addEdge((idx << 1) | 1, sink, inf);
      } else if (grid[i][j] == 'C') {
        source = (idx << 1) | 1;
      }
      if (grid[i][j] != '#') {
        dinic.addEdge(idx << 1, (idx << 1) | 1, grid[i][j] == '.' ? 1 : inf);
        FOR(dir, 0, 4) {
          int newI = i + DX[dir], newJ = j + DY[dir];
          if (0 <= newI && newI < 2 && 0 <= newJ && newJ < m && grid[newI][newJ] != '#') {
            dinic.addEdge((idx << 1) | 1, (newI * m + newJ) << 1, inf);
          }
        }
      }
      ++idx;
    }
    int res = dinic.calcFlow<int>(source, sink);
    return source < 0 || res >= inf ? -1 : res;
  }
};

#ifdef LOCAL
int main() {
  lc::handle<Solution>(tests);
  return 0;
}
#endif
