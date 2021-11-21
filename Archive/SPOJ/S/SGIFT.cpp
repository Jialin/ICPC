// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  vector<int> as(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
  }
  SORT(as);
  vector<int64_t> sums(n);
  int disCnt = 0;
  FOR(i, 0, n) {
    if (i && as[i - 1] != as[i]) {
      ++disCnt;
    }
    sums[disCnt] += as[i];
  }
  UNIQUE(as);
  disCnt = SIZE(as);
  FOR(i, 1, disCnt) {
    sums[i] += sums[i - 1];
  }
  int q;
  io::readInt(q);
  FOR(i, 0, q) {
    int lower, upper;
    io::readInt(lower);
    io::readInt(upper);
    lower = INDEX(as, lower);
    upper = INDEX(as, upper + 1);
    if (lower >= upper || !upper) {
      io::writeChar('0');
    } else {
      io::writeInt(lower ? sums[upper - 1] - sums[lower - 1] : sums[upper - 1]);
    }
    io::writeChar('\n');
  }
}
