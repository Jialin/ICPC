// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SLIDING_WINDOW_RESERVE
#include "ds/sliding_window/base_sliding_window_macros.h"

#include "ds/sliding_window/max_sliding_window.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, m, maxShotCnt;
  io::readInt(n);
  io::readInt(m);
  io::readInt(maxShotCnt);
  vector<ds::MaxSlidingWindow<int>> shots(m);
  FOR(j, 0, m) {
    shots[j].reserve(n);
    shots[j].init(n);
  }
  int resLength = 0;
  vector<int> res(m);
  int start = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      int v;
      io::readInt(v);
      shots[j].push_back(i, v);
    }
    while (true) {
      int shotCnt = 0;
      FOR(j, 0, m) {
        shotCnt += shots[j].empty() ? 0 : shots[j].get().second;
      }
      if (shotCnt <= maxShotCnt) {
        break;
      }
      ++start;
      FOR(j, 0, m) {
        shots[j].popFrontUntilIdx(start);
      }
    }
    if (resLength < i - start + 1) {
      resLength = i - start + 1;
      FOR(j, 0, m) {
        res[j] = shots[j].empty() ? 0 : shots[j].get().second;
      }
    }
  }
  FOR(j, 0, m) {
    io::writeInt(res[j]);
    io::writeChar(j + 1 == m ? '\n' : ' ');
  }
}
