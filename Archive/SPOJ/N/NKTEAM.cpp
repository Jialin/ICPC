// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define STAIR_CONTAINER_IS_FULLY_INSIDE
#define STAIR_CONTAINER_UPDATE
#include "ds/stair_container_macros.h"

#include "ds/stair_container.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 500000;

int n;
int as[MAXN], bs[MAXN], cs[MAXN], orders[MAXN];

int main() {
  io::readInt(n);
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    as[v - 1] = n - i;
  }
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    bs[v - 1] = n - i;
  }
  FOR(i, 0, n) {
    int v;
    io::readInt(v);
    cs[v - 1] = n - i;
    orders[i] = i;
  }
  sort(orders, orders + n, [](int x, int y) {
    return as[x] > as[y];
  });
  int res = n;
  ds::StairContainer<int> stairs;
  FOR(i, 0, n) {
    int idx = orders[i];
    if (stairs.isFullyInside(bs[idx], cs[idx])) {
      --res;
    } else {
      stairs.update(bs[idx], cs[idx]);
    }
  }
  io::writeInt(res);
  io::writeChar('\n');
}
