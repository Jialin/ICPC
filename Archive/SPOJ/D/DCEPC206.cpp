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

const int MAXN = 100000;

int n;
vector<int> as, dis;
ds::FenwickSum<int64_t> fen;

int main() {
  as.reserve(MAXN);
  dis.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readInt(n);
    as.resize(n);
    FOR(i, 0, n) {
      io::readInt(as[i]);
    }
    dis = as;
    SORTUNIQUE(dis);
    fen.init(SIZE(dis));
    int64_t res = 0;
    for (int a : as) {
      int idx = INDEX(dis, a);
      if (idx) {
        res += fen.calcPrefix(idx - 1);
      }
      fen.update(idx, a);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
