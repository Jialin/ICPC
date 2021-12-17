// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int BLOCK = 800;

vector<int> cnts;
vector<int> lastPs;

inline void update(int p, int nxtP, int bound) {
  if (nxtP < bound) {
    cnts[p] = cnts[nxtP] + 1;
    lastPs[p] = lastPs[nxtP];
  } else {
    cnts[p] = 0;
    lastPs[p] = p;
  }
}

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  cnts.resize(n);
  lastPs.resize(n);
  int bound = n;
  for (int i = n - 1, j = i / BLOCK, k = i % BLOCK; i >= 0; --i, --k) {
    if (k < 0) {
      bound = i + 1;
      k = BLOCK - 1;
      --j;
    }
    update(i, i + vs[i], bound);
  }
  FOR(_, 0, q) {
    int op, idx;
    io::readInt(op);
    io::readInt(idx);
    --idx;
    if (op) {
      int resCnt = 0, resLast = idx;
      while (idx < n) {
        resLast = lastPs[idx];
        resCnt += cnts[idx] + 1;
        idx = resLast + vs[resLast];
      }
      io::writeInt(resLast + 1);
      io::writeChar(' ');
      io::writeInt(resCnt);
      io::writeChar('\n');
    } else {
      int v;
      io::readInt(v);
      vs[idx] = v;
      int lowerBound = idx / BLOCK * BLOCK;
      int upperBound = min(lowerBound + BLOCK, n);
      for (int i = idx; i >= lowerBound; --i) {
        update(i, i + vs[i], upperBound);
      }
    }
  }
  return 0;
}
