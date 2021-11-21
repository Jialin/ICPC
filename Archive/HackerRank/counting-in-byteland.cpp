// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_3D_ARRAY_CALC_RANGE
#include "ds/fenwick/base_fenwick_3d_array_macros.h"

#include "ds/fenwick/fenwick_3d_array_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100 + 1;

int n;
ds::Fenwick3DArraySum<int64_t, MAXN, MAXN, MAXN> fen;

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  ++n;
  fen.init(n, n, n);
  int64_t sum = 0;
  FOR(_, 0, q) {
    int op, x, y, z;
    io::readInt(op);
    io::readInt(x);
    io::readInt(y);
    io::readInt(z);
    if (op == 1) {
      int v;
      scanf("%d", &v);
      io::readInt(v);
      fen.update(x, y, z, v);
      sum += v;
    } else {
      int x2, y2, z2;
      io::readInt(x2);
      io::readInt(y2);
      io::readInt(z2);
      io::writeInt(sum - fen.calcRange(x, y, z, x2 + 1, y2 + 1, z2 + 1));
      io::writeChar('\n');
    }
  }
}
