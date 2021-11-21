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
#include "math/mod/add.h"
#include "math/mod/mul.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000;
const int MOD = 1000000007;

int n, as[MAXN], facts[MAXN];
ds::FenwickSum<int> fen;

int main() {
  facts[0] = 1;
  FOR(i, 1, MAXN) {
    facts[i] = math::mulMod(facts[i - 1], i, MOD);
  }
  fen.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    fen.init(n);
    int res = 1;
    FOR(i, 0, n) {
      int v;
      io::readInt(v);
      fen.update(--v, 1);
      res = math::addMod(res, math::mulMod(v - fen.calcPrefix(v) + 1, facts[n - 1 - i], MOD), MOD);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
