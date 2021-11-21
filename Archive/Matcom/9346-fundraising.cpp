// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_PREFIX_RETURN
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_max.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct Person {
  int b, f;
  int64_t d;

  inline void init() {
    io::readInt(b);
    io::readInt(f);
    io::readInt(d);
  }

  inline bool operator<(const Person& o) const {
    return b < o.b || (b == o.b && f > o.f);
  }
};

const int MAXN = 100000;

Person persons[MAXN];

int main() {
  int n;
  io::readInt(n);
  FOR(i, 0, n) {
    persons[i].init();
  }
  sort(persons, persons + n);
  int m = 1;
  for (int i = 1; i < n; ++i) {
    if (persons[m - 1].b == persons[i].b && persons[m - 1].f == persons[i].f) {
      persons[m - 1].d += persons[i].d;
    } else {
      swap(persons[m++], persons[i]);
    }
  }
  n = m;
  vector<int> dis(n);
  FOR(i, 0, n) {
    dis[i] = persons[i].f;
  }
  SORTUNIQUE(dis);
  ds::FenwickMax<int64_t> fen;
  fen.init(SIZE(dis));
  int64_t res = 0;
  FOR(i, 0, n) {
    const auto& person = persons[i];
    int idx = INDEX(dis, person.f);
    int64_t subRes = idx ? fen.calcPrefix(idx - 1) : 0;
    // DEBUGF("b:%d f:%d(%d) d:%d subRes:%lld\n", person.b, person.f, idx, person.d, subRes);
    if (subRes < 0) {
      subRes = person.d;
    } else {
      subRes += person.d;
    }
    fen.update(idx, subRes);
    res = max(res, subRes);
  }
  io::writeInt(res);
  io::writeChar('\n');
  return 0;
}
