// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_2D_ARRAY_CALC_RANGE
#include "ds/fenwick/base_fenwick_2d_array_macros.h"

#include "ds/fenwick/fenwick_2d_array_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1024;

ds::Fenwick2DArraySum<int, MAXN, MAXN> fen;
char op[4];
int vs[MAXN][MAXN];

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    fen.init(n, n);
    FOR(i, 0, n) {
      memset(vs[i], 0, sizeof(int) * n);
    }
    while (true) {
      io::readCharArray(op);
      if (op[1] == 'N') {
        break;
      }
      if (op[1] == 'E') {
        int x, y, delta;
        io::readInt(x);
        io::readInt(y);
        io::readInt(delta);
        fen.update(x, y, delta - vs[x][y]);
        vs[x][y] = delta;
      } else {
        int x1, y1, x2, y2;
        io::readInt(x1);
        io::readInt(y1);
        io::readInt(x2);
        io::readInt(y2);
        printf("%d\n", fen.calcRange(x1, y1, x2 + 1, y2 + 1));
      }
    }
    putchar('\n');
  }
  return 0;
}
