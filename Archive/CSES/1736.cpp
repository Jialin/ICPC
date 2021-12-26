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
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int64_t> vs(n);
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    vs[i] = i ? vs[i - 1] + v : v;
  }
  ds::FenwickSum<int64_t> fen0, fen1, fen2;
  fen0.init(n);
  fen1.init(n);
  fen2.init(n);
  FOR(_, 0, q) {
    int op, lower, upper;
    io::readInt(op);
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    if (op == 1) {
      fen2.update(lower, 1);
      fen2.update(upper, -1);
      fen1.update(lower, 3 - (lower << 1));
      fen1.update(upper, (lower << 1) - 3);
      int64_t x = (lower - 1LL) * (lower - 2);
      fen0.update(lower, x);
      fen0.update(upper, (upper - lower) * (upper - lower + 1LL) - x);
    } else {
      int64_t res = (fen2.calcPrefix(upper) * (upper - 1) + fen1.calcPrefix(upper)) * (upper - 1) +
                    fen0.calcPrefix(upper);
      if (lower > 1) {
        res -= (fen2.calcPrefix(lower) * (lower - 1) + fen1.calcPrefix(lower)) * (lower - 1);
      }
      if (lower) {
        res -= fen0.calcPrefix(lower);
      }
      io::writeInt((res >> 1) + vs[upper - 1] - (lower ? vs[lower - 1] : 0), '\n');
    }
  }
  return 0;
}
