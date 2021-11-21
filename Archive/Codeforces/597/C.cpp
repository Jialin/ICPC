// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int n, m;
ds::FenwickSum<int64_t> fen;
vector<int> as;
vector<int64_t> cnts;

int main() {
  io::readInt(n);
  io::readInt(m);
  as.resize(n);
  FOR(i, 0, n) {
    io::readInt(as[i]);
    --as[i];
  }
  cnts.assign(n, 1);
  int64_t res;
  fen.reserve(n);
  for (int round = m - 1; round >= 0; --round) {
    fen.init(n);
    FOR(i, 0, n) {
      auto cnt = cnts[i];
      cnts[i] = as[i] ? fen.calcPrefix(as[i] - 1) : 0;
      fen.update(as[i], cnt);
    }
  }
  io::writeInt(accumulate(ALL(cnts), 0LL));
  io::writeChar('\n');
  return 0;
}
