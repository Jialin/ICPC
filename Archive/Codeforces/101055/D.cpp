// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_2D_ARRAY_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_max.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000;

ds::Fenwick2DArrayMax<int, MAXN, MAXN> fen;

int main() {
  int n;
  io::readInt(n);
  int res = 0;
  fen.init(MAXN, MAXN);
  FOR(_, 0, n) {
    int x, y;
    io::readInt(x);
    io::readInt(y);
    --x;
    --y;
    int subRes = max(fen.calcPrefix(x, y), 0) + 1;
    res = max(res, subRes);
    fen.update(x, y, subRes);
  }
  io::writeInt(res);
  io::writeChar('\n');
  return 0;
}
