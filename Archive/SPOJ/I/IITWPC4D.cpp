// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_KTH
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;

int main() {
  vector<int> as;
  as.reserve(MAXN);
  ds::FenwickSum<int> fen;
  fen.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    as.resize(n);
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      io::readInt(as[i]);
      as[i] = i - as[i];
      if (valid && as[i] < 0) {
        valid = false;
      }
    }
    io::writeCharArray("Test : ");
    io::writeInt(taskIdx);
    io::writeChar('\n');
    if (!valid) {
      io::writeChar('-');
      io::writeChar('1');
      io::writeChar('\n');
      continue;
    }
    fen._n = n;
    fen._vs.resize(n);
    FOR(i, 0, n) {
      fen._vs[i] = 1 << __builtin_ctz(i + 1);
    }
    for (int i = n - 1; i >= 0; --i) {
      int idx = fen.calcKth(as[i]);
      as[i] = idx;
      fen.update(idx, -1);
    }
    FOR(i, 0, n) {
      io::writeInt(as[i] + 1, i + 1 == n ? '\n' : ' ');
    }
  }
  return 0;
}
