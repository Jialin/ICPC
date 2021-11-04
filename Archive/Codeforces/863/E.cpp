// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  vector<tuple<int, int, int>> bounds;
  for (int i = 0; i < n; ++i) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    bounds.emplace_back(l, r, i);
  }
  SORT(bounds);
  int lower, upper, lastIdx;
  tie(lower, upper, lastIdx) = bounds[0];
  int res = -1;
  FOR(i, 1, n) {
    int l, r, idx;
    tie(l, r, idx) = bounds[i];
    if (r <= upper) {
      res = idx + 1;
      break;
    }
    if (l <= lower && r >= upper) {
      res = lastIdx + 1;
      break;
    }
    lower = max(upper + 1, l);
    upper = r;
    lastIdx = idx;
  }
  io::writeInt(res);
  io::writeChar('\n');
}
