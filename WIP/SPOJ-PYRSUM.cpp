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

const int MAXQ = 1000;

ds::FenwickSum<int64_t> fen1, fen0;
ds::FenwickSum<int> fen2;
char op[8];
char ops[MAXQ];
int xs[MAXQ], ys[MAXQ];
int lowerBound, upperBound;

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int q;
    io::readInt(q);
    lowerBound = 1000000;
    upperBound = 0;
    FOR(i, 0, q) {
      io::readCharArray(op);
      ops[i] = op[0];
      io::readInt(xs[i]);
      io::readInt(ys[i]);
      --xs[i];
      if (op[0] == 'b') {
        lowerBound = min(lowerBound, xs[i] - (ys[i] >> 1));
        upperBound = max(upperBound, xs[i] + (ys[i] >> 1) + 2);
      }
    }
    upperBound = max(upperBound, lowerBound + 1);
    int size = upperBound - lowerBound;
    fen0.init(size);
    fen1.init(size);
    fen2.init(size);
    FOR(i, 0, q) {
      if (ops[i] == 'b') {
        int center = xs[i] - lowerBound, width = ys[i];
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
        int lower = xs[i] - lowerBound, upper = ys[i] - lowerBound;
        lower = max(lower, 0);
        upper = min(upper, size);
        int64_t res;
        if (lower < upper) {
          res = fen0.calcRange(lower, upper);
          res += fen1.calcPrefix(upper - 1) * (upper - 1);
          res += fen2.calcPrefix(upper - 1) * (upper - 1LL) * (upper - 1);
          if (lower) {
            res -= fen1.calcPrefix(lower - 1) * (lower - 1);
            res -= fen2.calcPrefix(lower - 1) * (lower - 1LL) * (lower - 1);
          }
        } else {
          res = 0;
        }
        io::writeInt(res >> 1);
        io::writeChar('\n');
      }
    }
    io::writeChar('\n');
  }
}
