// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXM = 1000000 + 1;

int lastPos[MAXM];

int main() {
  int n;
  io::readInt(n);
  vector<int> poss(n);
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    poss[i] = lastPos[v] - 1;
    lastPos[v] = i + 1;
  }
  int q;
  io::readInt(q);
  vector<tuple<int, int, int>> queries;
  queries.reserve(q);
  FOR(i, 0, q) {
    int x, y;
    io::readInt(x);
    io::readInt(y);
    queries.emplace_back(x - 1, y, i);
  }
  sort(ALL(queries), [](const auto& lv, const auto& rv) {
    return get<1>(lv) < get<1>(rv);
  });
  int total = 0;
  ds::FenwickSum<int> fen;
  fen.init(n);
  vector<int> ress(q);
  int lastIdx = -1;
  for (const auto& [lower, upper, idx] : queries) {
    FOR(i, lastIdx + 1, upper) {
      fen.update(i, 1);
      ++total;
      if (poss[i] >= 0) {
        fen.update(poss[i], -1);
        --total;
      }
    }
    ress[idx] = lower ? total - fen.calcPrefix(lower - 1) : total;
    lastIdx = upper - 1;
  }
  for (int res : ress) {
    io::writeInt(res);
    io::writeChar('\n');
  }
}
