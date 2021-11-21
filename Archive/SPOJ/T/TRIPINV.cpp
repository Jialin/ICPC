// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

int n, as[MAXN], leftCnts[MAXN];
ds::FenwickSum<int> fen;

int main() {
  io::readInt(n);
  fen.init(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
    --as[i];
    leftCnts[i] = n - 1 - as[i] ? fen.calcPrefix(n - 2 - as[i]) : 0;
    fen.update(n - 1 - as[i], 1);
  }
  fen.init(n);
  int64_t res = 0;
  for (int i = n - 1; i >= 0; --i) {
    res += (as[i] ? fen.calcPrefix(as[i] - 1) : 0) * (leftCnts[i] + 0LL);
    fen.update(as[i], 1);
  }
  io::writeInt(res);
  io::writeChar('\n');
  return 0;
}
