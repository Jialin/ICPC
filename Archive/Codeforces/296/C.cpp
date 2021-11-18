// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, m, k;
  io::readInt(n);
  io::readInt(m);
  io::readInt(k);
  vector<int> as(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
  }
  vector<int> lowers(m), uppers(m), deltas(m);
  FOR(i, 0, m) {
    io::readInt(lowers[i]);
    io::readInt(uppers[i]);
    io::readInt(deltas[i]);
  }
  vector<int> opCnts(m + 1);
  FOR(_, 0, k) {
    int x, y;
    io::readInt(x);
    io::readInt(y);
    ++opCnts[x - 1];
    --opCnts[y];
  }
  vector<int64_t> aDeltas(n + 1);
  FOR(i, 0, m) {
    if (i) {
      opCnts[i] += opCnts[i - 1];
    }
    aDeltas[lowers[i] - 1] += (opCnts[i] + 0LL) * deltas[i];
    aDeltas[uppers[i]] -= (opCnts[i] + 0LL) * deltas[i];
  }
  FOR(i, 0, n) {
    if (i) {
      aDeltas[i] += aDeltas[i - 1];
    }
    io::writeInt(as[i] + aDeltas[i]);
    io::writeChar(i + 1 == n ? '\n' : ' ');
  }
}
