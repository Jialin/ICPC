// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SLIDING_WINDOW_RESERVE
#include "ds/sliding_window/base_sliding_window_macros.h"

#include "ds/sliding_window/min_sliding_window.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000 + 1;

int n, m, x, y;
int hs[MAXN][MAXN], minRowHs[MAXN][MAXN];
int64_t sumHs[MAXN][MAXN], costs[MAXN][MAXN];
bool used[MAXN][MAXN];
ds::MinSlidingWindow<int> sw;

int main() {
  io::readInt(n);
  io::readInt(m);
  io::readInt(x);
  io::readInt(y);
  FOR(i, 1, n + 1) {
    sw.init(y);
    FOR(j, 1, m + 1) {
      io::readInt(hs[i][j]);
      sumHs[i][j] = sumHs[i - 1][j] + sumHs[i][j - 1] - sumHs[i - 1][j - 1] + hs[i][j];
      sw.push_back(j, hs[i][j]);
      if (j >= y) {
        minRowHs[i][j] = sw.calc().second;
      }
    }
  }
  vector<tuple<int64_t, int, int>> tries;
  int64_t xy = (x + 0LL) * y;
  tries.reserve((n - x + 1) * (m - y + 1));
  FOR(j, y, m + 1) {
    sw.init(x);
    FOR(i, 1, n + 1) {
      sw.push_back(i, minRowHs[i][j]);
      if (i >= x) {
        costs[i][j] = sumHs[i][j] - sumHs[i - x][j] - sumHs[i][j - y] + sumHs[i - x][j - y] -
                      sw.calc().second * xy;
        tries.emplace_back(costs[i][j], i, j);
      }
    }
  }
  SORT(tries);
  vector<tuple<int, int, int64_t>> res;
  for (const auto& [cost, i, j] : tries) {
    if (used[i][j]) {
      continue;
    }
    res.emplace_back(i - x + 1, j - y + 1, cost);
    int aBound = min(i + x - 1, n) + 1;
    int bBound = min(j + y - 1, m) + 1;
    FOR(a, i - x + 1, aBound) FOR(b, j - y + 1, bBound) {
      used[a][b] = true;
    }
  }
  io::writeInt(SIZE(res));
  io::writeChar('\n');
  for (const auto& [i, j, cost] : res) {
    io::writeInt(i);
    io::writeChar(' ');
    io::writeInt(j);
    io::writeChar(' ');
    io::writeInt(cost);
    io::writeChar('\n');
  }
}
