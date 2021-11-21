// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

char op[2];

int main() {
  int n, q, c;
  io::readInt(n);
  io::readInt(q);
  io::readInt(c);
  ds::FenwickSum<int64_t> fen;
  fen.init(n);
  fen.update(0, c);
  FOR(_, 0, q) {
    io::readCharArray(op);
    if (op[0] == 'S') {
      int u, v, delta;
      io::readInt(u);
      io::readInt(v);
      io::readInt(delta);
      fen.update(u - 1, delta);
      fen.update(v, -delta);
    } else {
      int idx;
      io::readInt(idx);
      io::writeInt(fen.calcPrefix(idx - 1));
      io::writeChar('\n');
    }
  }
}
