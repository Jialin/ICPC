// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n;
  io::readInt(n);
  vector<int> ps(n);
  FOR(i, 0, n) {
  io::readInt(ps[i]);
    ps[i] = n - ps[i];
  }
  ds::FenwickSum<int64_t> fen;
  fen.init(n);
  int64_t resCnt = 0;
  for (auto p : ps) {
    resCnt += fen.calcPrefix(p);
    fen.update(p, 1);
  }
  int64_t resCnt2 = 0, resCnt3 = 0, exp = 0;
  fen.init(n);
  FOR(i, 0, n) {
    resCnt2 += (n - i) * fen.calcPrefix(ps[i]);
    fen.update(ps[i], i + 1);
    exp += i;
    resCnt3 += exp * (n - i + 0LL);
  }
  printf("%.16lf\n", resCnt - ((resCnt2 << 1) - resCnt3 + 0.) / n / (n + 1));
}
