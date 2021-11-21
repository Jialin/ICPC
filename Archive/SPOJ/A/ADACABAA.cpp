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

int n;

struct Vege {
  int a, b, c, d;

  inline void init() {
    io::readInt(a);
    io::readInt(b);
    --b;
    io::readInt(c);
    c = n - c;
    io::readInt(d);
    d = n - d;
  }

  inline bool operator<(const Vege& o) const {
    return a < o.a;
  }
};

const int MAXN = 200000;

ds::StairContainer<int> stairs[MAXN];
Vege veges[MAXN];

inline bool isFullyCovered(const Vege& vege) {
  if (!vege.b) {
    return false;
  }
  for (int i = vege.b - 1; i >= 0; --i) {
    if (stairs[i].isFullyInside(vege.c, vege.d)) {
      return true;
    }
    i &= i + 1;
  }
  return false;
}

inline void update(const Vege& vege) {
  for (int i = vege.b; i < n; i |= i + 1) {
    stairs[i].update(vege.c, vege.d);
  }
}

int main() {
  io::readInt(n);
  FOR(i, 0, n) {
    veges[i].init();
  }
  sort(veges, veges + n);
  int res = 0;
  FOR(i, 0, n) {
    const auto& vege = veges[i];
    if (!isFullyCovered(vege)) {
      ++res;
    }
    update(vege);
  }
  io::writeInt(res);
  io::writeChar('\n');
}
