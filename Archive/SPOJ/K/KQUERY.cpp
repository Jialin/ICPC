// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_RANGE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct Query {
  int v, lower, upper, idx;
  bool isQuery;

  inline Query(int v, int idx) : v(v), idx(idx), isQuery(false) {}

  inline Query(int v, int lower, int upper, int idx)
      : v(v), lower(lower), upper(upper), idx(idx), isQuery(true) {}

  inline bool operator<(const Query& o) const {
    if (v == o.v) {
      return isQuery > o.isQuery;
    }
    return v > o.v;
  }

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const Query& query) {
    return o
           << '('
           << (query.isQuery
                   ? tostring2(
                         "v", query.v, "lower", query.lower, "upper", query.upper, "idx", query.idx)
                   : tostring2("v", query.v, "idx", query.idx))
           << ')';
  }
#endif
};

int main() {
  int n;
  io::readInt(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  int q;
  io::readInt(q);
  vector<Query> queries;
  queries.reserve(n + q);
  FOR(i, 0, n) {
    queries.emplace_back(vs[i], i);
  }
  FOR(i, 0, q) {
    int lower, upper, v;
    io::readInt(lower);
    io::readInt(upper);
    io::readInt(v);
    queries.emplace_back(v, lower - 1, upper, i);
  }
  SORT(queries);
  ds::FenwickSum<int> fen;
  fen.init(n);
  vector<int> results(q);
  for (const auto& query : queries) {
    if (query.isQuery) {
      results[query.idx] = fen.calcRange(query.lower, query.upper);
    } else {
      fen.update(query.idx, 1);
    }
  }
  FOR(i, 0, q) {
    io::writeInt(results[i], '\n');
  }
  return 0;
}
