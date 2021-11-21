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

vector<pair<int, int>> points;
vector<int> dis;
ds::FenwickSum<int> fen;

int main() {
  points.reserve(MAXN);
  dis.reserve(MAXN);
  fen.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, threshold;
    io::readInt(n);
    io::readInt(threshold);
    points.clear();
    dis.clear();
    FOR(i, 0, n) {
      int x, y;
      io::readInt(x);
      io::readInt(y);
      dis.push_back(y);
      points.emplace_back(x, y);
    }
    SORT(points);
    SORTUNIQUE(dis);
    fen.init(SIZE(dis));
    int res = 0;
    for (auto [x, y] : points) {
      y = INDEX(dis, y);
      if (abs(fen.calcPrefix(y) * 2 - n + 1) >= threshold) {
        ++res;
      }
      fen.update(y, 1);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
