// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/adapter.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct Bowl {
  int x, delta;

  inline bool operator<(const Bowl& o) const {
    return delta < o.delta;
  }
};

const int MAXN = 200000;

Bowl bowls[MAXN];

int main() {
  int n, tl;
  io::readInt(n);
  io::readInt(tl);
  int m = 0;
  FOR(i, 0, n) {
    int t;
    io::readInt(t);
    if (i + 1 >= tl || t >= tl) {
      continue;
    }
    bowls[m].x = i + 1;
    bowls[m++].delta = t - i - 1;
  }
  n = m;
  sort(bowls, bowls + n);
  ds::Adapter<priority_queue<int>> heap;
  heap.container().reserve(n);
  int res = 0;
  FOR(i, 0, n) {
    const auto& bowl = bowls[i];
    if (bowl.delta <= 0) {
      res = i + 1;
    } else {
      for (; !heap.empty() && heap.top() >= tl - bowl.delta; heap.pop()) {}
      res = max(res, SIZE(heap.container()) + 1);
    }
    heap.push(bowl.x);
  }
  io::writeInt(res);
  io::writeChar('\n');
  return 0;
}
