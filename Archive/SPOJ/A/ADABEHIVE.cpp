// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_2D_ARRAY_CALC_RANGE
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 2000;

ds::Fenwick2DArraySum<int64_t, MAXN, MAXN> fen;

int main() {
  int n, m, q;
  io::readInt(n);
  io::readInt(m);
  io::readInt(q);
  fen.init(n, m);
  FOR(i, 0, n) FOR(j, 0, m) {
    int v;
    io::readInt(v);
    fen.update(i, j, v);
  }
  FOR(_, 0, q) {
    int op;
    io::readInt(op);
    if (op == 1) {
      int x, y, d;
      io::readInt(x);
      io::readInt(y);
      io::readInt(d);
      fen.update(x - 1, y - 1, d);
    } else {
      int x1, y1, x2, y2;
      io::readInt(x1);
      io::readInt(y1);
      io::readInt(x2);
      io::readInt(y2);
      io::writeInt(fen.calcRange(x1 - 1, y1 - 1, x2, y2));
      io::writeChar('\n');
    }
  }
  return 0;
}
