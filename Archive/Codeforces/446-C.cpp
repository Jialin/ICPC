// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX
#include "ds/fenwick/base_fenwick_macros.h"
#define MOD_INT_ADD
#define MOD_INT_ADD_INLINE
#define MOD_INT_INIT_ADD
#define MOD_INT_MUL
#define MOD_INT_NEGATE
#define MOD_INT_SUB
#define MOD_INT_SUB_INLINE
#include "math/mod/mod_int_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/mod/mod_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000009;

using ModInt = math::ModInt<int, int64_t, MOD>;

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<ModInt> psums;
  psums.resize(n + 1);
  psums[0]._v = 0;
  FOR(i, 0, n) {
    io::readInt(psums[i + 1]._v);
    psums[i + 1] += psums[i];
  }
  int n5 = n + 5;
  vector<ModInt> fibs(n5);
  fibs[0] = 0;
  fibs[1] = 1;
  FOR(i, 2, n5) {
    fibs[i].initAdd(fibs[i - 2], fibs[i - 1]);
  }
  ds::FenwickSum<ModInt> fen1, fen2, fen3;
  fen1.init(n);
  fen2.init(n);
  fen3.init(n);
  FOR(_, 0, q) {
    int op, lower, upper;
    io::readInt(op);
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    if (op == 1) {
      fen1.update(lower, (lower & 1) ? -fibs[lower + 1] : fibs[lower + 1]);
      fen1.update(upper, (lower & 1) ? fibs[lower + 1] : -fibs[lower + 1]);
      fen2.update(lower, (lower & 1) ? fibs[lower] : -fibs[lower]);
      fen2.update(upper, (lower & 1) ? -fibs[lower] : fibs[lower]);
      fen3.update(lower, -1);
      fen3.update(upper, fibs[upper - lower + 2]);
    } else {
      auto res = psums[upper] - psums[lower];
      res += fen1.calcPrefix(upper) * fibs[upper + 2];
      res -= fen1.calcPrefix(lower) * fibs[lower + 2];
      res += fen2.calcPrefix(upper) * fibs[upper + 3];
      res -= fen2.calcPrefix(lower) * fibs[lower + 3];
      res += fen3.calcPrefix(upper);
      res -= fen3.calcPrefix(lower);
      io::writeInt(res._v, '\n');
    }
  }
  return 0;
}
