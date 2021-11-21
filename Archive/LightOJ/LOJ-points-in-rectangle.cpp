// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_2D_ARRAY_CALC_RANGE
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_sum.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000 + 1;

ds::Fenwick2DArraySum<int, MAXN, MAXN> fen;
int covered[MAXN][MAXN];

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    fen.init(MAXN, MAXN);
    int q;
    io::readInt(q);
    io::writeCharArray("Case ");
    io::writeInt(taskIdx);
    io::writeCharArray(":\n");
    FOR(_, 0, q) {
      int op, x, y;
      io::readInt(op);
      io::readInt(x);
      io::readInt(y);
      if (op == 1) {
        int x2, y2;
        io::readInt(x2);
        io::readInt(y2);
        io::writeInt(fen.calcRange(x, y, x2 + 1, y2 + 1));
        io::writeChar('\n');
      } else if (covered[x][y] != taskIdx) {
        fen.update(x, y, 1);
        covered[x][y] = taskIdx;
      }
    }
  }
  return 0;
}
