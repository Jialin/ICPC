// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/disjoint_set/base_disjoint_set_value_macros.h"
#define BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/disjoint_set/disjoint_set_max.h"
#include "ds/fenwick/fenwick_sum.h"
#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/prime/min_prime_tagger.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000000 + 1;

int d[MAXN];

inline void init() {
  math::MinPrimeTagger tagger;
  tagger.init(MAXN);
  d[1] = 1;
  FOR(i, 2, MAXN) {
    int prime, primeCnt, j;
    tagger.process(i, prime, primeCnt, j);
    d[i] = d[j] * (primeCnt + 1);
  }
}

int main() {
  init();
  int n, q;
  io::readInt(n);
  io::readInt(q);
  ds::FenwickSum<int64_t> fen;
  fen.init(n);
  vector<int> idxs(n);
  vector<int> vs(n);
  FOR(i, 0, n) {
    idxs[i] = i;
    io::readInt(vs[i]);
    fen.update(i, vs[i]);
  }
  ds::DisjointSetMax<int> dset;
  dset.init(move(idxs));
  FOR(i, 1, n) {
    if (vs[i - 1] < 3 && vs[i] < 3) {
      dset.unionSet(i - 1, i);
    }
  }
  FOR(_, 0, q) {
    int op, lower, upper;
    io::readInt(op);
    io::readInt(lower);
    io::readInt(upper);
    --lower;
    if (op == 1) {
      FOR(i, lower, upper) {
        if (vs[i] < 3) {
          i = dset.calcSetValue(i);
          continue;
        }
        int newV = d[vs[i]];
        fen.update(i, newV - vs[i]);
        vs[i] = newV;
        if (newV < 3) {
          if (i && vs[i - 1] < 3) {
            dset.unionSet(i - 1, i);
          }
          if (i + 1 < n && vs[i + 1] < 3) {
            dset.unionSet(i, i + 1);
          }
        }
      }
    } else {
      io::writeInt(fen.calcRange(lower, upper), '\n');
    }
  }
  return 0;
}
