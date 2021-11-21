// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000;

ds::FenwickSum<int> fen;
short as[MAXN];
char ops[8];

int main() {
  fen.reserve(MAXN);
  int taskIdx = 0;
  int n;
  while (true) {
    io::readInt(n);
    if (!n) {
      break;
    }
    fen.init(n);
    FOR(i, 0, n) {
      io::readInt(as[i]);
      fen.update(i, as[i]);
    }
    if (taskIdx) {
      io::writeChar('\n');
    }
    io::writeCharArray("Case ");
    io::writeInt(++taskIdx);
    io::writeCharArray(":\n");
    while (true) {
      io::readCharArray(ops);
      if (ops[0] == 'E') {
        break;
      }
      if (ops[0] == 'S') {
        int x;
        short v;
        io::readInt(x);
        --x;
        io::readInt(v);
        fen.update(x, v - as[x]);
        as[x] = v;
      } else {
        int x, y;
        io::readInt(x);
        io::readInt(y);
        io::writeInt(fen.calcRange(x - 1, y));
        io::writeChar('\n');
      }
    }
  }
  return 0;
}
