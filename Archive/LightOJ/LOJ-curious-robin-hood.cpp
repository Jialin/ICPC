// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

ds::FenwickSum<int> fen;
vector<int> as;

int main() {
  fen.reserve(MAXN);
  as.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, q;
    io::readInt(n);
    io::readInt(q);
    as.resize(n);
    fen.init(n);
    FOR(i, 0, n) {
      io::readInt(as[i]);
      fen.update(i, as[i]);
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeCharArray(":\n");
    FOR(_, 0, q) {
      int op, x;
      io::readInt(op);
      io::readInt(x);
      if (op == 3) {
        int y;
        io::readInt(y);
        io::writeInt(fen.calcRange(x, y + 1));
        io::writeChar('\n');
        continue;
      }
      int y;
      if (op == 2) {
        io::readInt(y);
      } else {
        y = -as[x];
        io::writeInt(as[x]);
        io::writeChar('\n');
      }
      fen.update(x, y);
      as[x] += y;
    }
  }
  return 0;
}
