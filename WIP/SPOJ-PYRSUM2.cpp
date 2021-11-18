// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#define BASE_FENWICK_CALC_RANGE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000000 + 10;

ds::FenwickSum<int64_t> fen1, fen0;
ds::FenwickSum<int> fen2;
char op[8];

int main() {
  int q;
  io::readInt(q);
  fen0.init(MAXN);
  fen1.init(MAXN);
  fen2.init(MAXN);
  FOR(_, 0, q) {
    io::readCharArray(op);
    if (op[0] == 'b') {
      int center, width;
      io::readInt(center);
      io::readInt(width);
      --center;
      int lower, upper;
      // left
      lower = center - (width >> 1);
      upper = center + 1;
      fen2.update(lower, 1);
      fen2.update(upper, -1);
      int delta1 = 3 - (lower << 1);
      fen1.update(lower, delta1);
      fen1.update(upper, -delta1);
      int64_t delta2 = (lower - 1LL) * (lower - 2);
      fen0.update(lower, delta2);
      fen0.update(upper, (upper - lower + 1LL) * (upper - lower) - delta2);
      // right
      if (width != 1) {
        lower = center + 1;
        upper = center + (width >> 1) + 2;
        fen2.update(lower, -1);
        fen2.update(upper, 1);
        int delta1 = (upper << 1) - 3;
        fen1.update(lower, delta1);
        fen1.update(upper, -delta1);
        int64_t delta2 = (lower + 2LL - (upper << 1)) * (lower - 1);
        fen0.update(lower, delta2);
        fen0.update(upper, (upper - lower - 1LL) * (upper - lower) - delta2);
      }
    } else {
      int lower, upper;
      io::readInt(lower);
      io::readInt(upper);
      --lower;
      int64_t res = fen0.calcRange(lower, upper);
      res += fen1.calcPrefix(upper - 1) * (upper - 1);
      res += fen2.calcPrefix(upper - 1) * (upper - 1LL) * (upper - 1);
      if (lower) {
        res -= fen1.calcPrefix(lower - 1) * (lower - 1);
        res -= fen2.calcPrefix(lower - 1) * (lower - 1LL) * (lower - 1);
      }
      io::writeInt(res >> 1);
      io::writeChar('\n');
    }
  }
}
