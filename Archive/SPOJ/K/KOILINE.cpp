// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_KTH
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  vector<int> hs(n);
  ds::FenwickSum<int> fen;
  fen._n = n;
  fen._vs.resize(n);
  FOR(i, 0, n) {
    io::readInt(hs[i]);
    fen._vs[i] = 1 << __builtin_ctz(i + 1);
  }
  SORT(hs);
  vector<int> cnts(n);
  FOR(i, 0, n) {
    io::readInt(cnts[i]);
  }
  FORR(i, n - 1, 0) {
    int idx = fen.calcKth(cnts[i]);
    cnts[i] = hs[idx];
    fen.update(idx, -1);
  }
  FOR(i, 0, n) {
    io::writeInt(cnts[i], '\n');
  }
  return 0;
}
