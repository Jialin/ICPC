// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, threshold;
  io::readInt(n);
  io::readInt(threshold);
  vector<int64_t> vs(n + 1);
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    vs[i + 1] = vs[i] + v - threshold;
  }
  auto dis = vs;
  SORTUNIQUE(dis);
  int64_t res = 0;
  ds::FenwickSum<int> fen;
  fen.init(SIZE(dis));
  FOR(i, 0, SIZE(vs)) {
    int idx = INDEX(dis, vs[i]);
    res += fen.calcPrefix(idx + 1);
    fen.update(idx, 1);
  }
  io::writeInt(res, '\n');
  return 0;
}
