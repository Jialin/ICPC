// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_KTH
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/mod/fix_inline.h"

// Last include
#include "debug/debug.h"

const int MAXN = 20000;

int main() {
  ds::FenwickSum<int> fen;
  fen.reserve(MAXN);
  vector<int> results;
  results.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    fen.init(n);
    FOR(i, 0, n) {
      fen.update(i, 1);
    }
    int pos = 0;
    results.resize(n);
    for (int i = 0, m = n; i < n; ++i, --m) {
      pos += i + 1;
      math::fixModInline(pos, m);
      int actualPos = fen.calcKth(pos);
      results[actualPos] = i + 1;
      fen.update(actualPos, -1);
    }
    FOR(i, 0, n) {
      io::writeInt(results[i], i + 1 == n ? '\n' : ' ');
    }
  }
  return 0;
}
