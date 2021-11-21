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

struct Tower {
  int a, b, h;

  void init() {
    io::readInt(a);
    io::readInt(b);
    io::readInt(h);
  }
};

const int MAXN = 100000;

int n;
Tower towers[MAXN];
vector<int> st;
vector<int64_t> hs;

int main() {
  io::readInt(n);
  FOR(i, 0, n) {
    towers[i].init();
  }
  sort(towers, towers + n, [](const auto& l, const auto& r) {
    return l.b > r.b || (l.b == r.b && l.a > r.a);
  });
  int64_t res = 0;
  FOR(i, 0, n) {
    const auto& tower = towers[i];
    for (; !st.empty() && towers[st.back()].a >= tower.b; st.pop_back(), hs.pop_back()) {}
    hs.push_back((st.empty() ? 0 : hs.back()) + tower.h);
    st.push_back(i);
    res = max(res, hs.back());
    DEBUGV(i);
    DEBUGV(st);
    DEBUGV(hs);
  }
  io::writeInt(res);
  io::writeChar('\n');
  return 0;
}
