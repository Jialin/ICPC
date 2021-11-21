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

int askCnt;

struct Query {
  int op, t, x, idx, askIdx;

  inline void init(int idx) {
    this->idx = idx;
    io::readInt(op);
    io::readInt(t);
    io::readInt(x);
    if (op == 3) {
      askIdx = askCnt++;
    }
  }

  inline bool operator<(const Query& o) const {
    return x < o.x || (x == o.x && idx < o.idx);
  }
};

const int MAXN = 1000000;

Query queries[MAXN];
int results[MAXN];
vector<int> dis;
ds::FenwickSum<int> fen;

void calc(int lower, int upper) {
  dis.clear();
  FOR(i, lower, upper) {
    if (queries[i].op != 3) {
      dis.push_back(queries[i].t);
    }
  }
  SORTUNIQUE(dis);
  int n = SIZE(dis);
  fen.init(n);
  FOR(i, lower, upper) {
    const auto& query = queries[i];
    int idx = INDEX(dis, query.t + 1);
    --idx;
    if (query.op == 1) {
      fen.update(idx, 1);
    } else if (query.op == 2) {
      fen.update(idx, -1);
    } else {
      results[query.askIdx] = idx >= 0 ? fen.calcPrefix(idx) : 0;
    }
  }
}

int main() {
  dis.reserve(MAXN);
  int q;
  io::readInt(q);
  askCnt = 0;
  FOR(i, 0, q) {
    queries[i].init(i);
  }
  sort(queries, queries + q);
  int lastPos = 0;
  FOR(i, 0, q) {
    if (i + 1 == q || queries[i].x != queries[i + 1].x) {
      calc(lastPos, i + 1);
      lastPos = i + 1;
    }
  }
  FOR(i, 0, askCnt) {
    io::writeInt(results[i]);
    io::writeChar('\n');
  }
}
