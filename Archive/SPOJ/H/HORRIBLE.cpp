// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

ds::FenwickSum<int64_t> fenA, fenB;

int main() {
  fenA.reserve(MAXN);
  fenB.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, q;
    io::readInt(n);
    io::readInt(q);
    fenA.init(n);
    fenB.init(n);
    FOR(_, 0, q) {
      int op, lower, upper;
      io::readInt(op);
      io::readInt(lower);
      io::readInt(upper);
      --lower;
      if (op) {
        io::writeInt(
            fenA.calcPrefix(upper - 1) * (upper - 1) -
            (lower ? fenA.calcPrefix(lower - 1) * (lower - 1) : 0) + fenB.calcRange(lower, upper));
        io::writeChar('\n');
      } else {
        int v;
        io::readInt(v);
        fenA.update(lower, v);
        fenA.update(upper, -v);
        fenB.update(lower, -v * (lower - 1LL));
        fenB.update(upper, v * (upper - 1LL));
      }
    }
  }
  return 0;
}
