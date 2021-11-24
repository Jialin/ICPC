// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_RESERVE
#include "ds/fenwick/base_fenwick_macros.h"

#include "ds/fenwick/fenwick_sum.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct Radio {
  int x, r, f;
  int xIdx, lowerIdx, upperIdx;

  inline void init() {
    io::readInt(x);
    io::readInt(r);
    io::readInt(f);
  }

  inline bool operator<(const Radio& o) const {
    return r < o.r;
  }
};

const int MAXN = 100000;

int m;
Radio radios[MAXN];
int idxs[MAXN], tmpIdxs[MAXN];
vector<int> dis;
ds::FenwickSum<int> fen;

int tag, tags[MAXN];

inline int64_t calc(int lower, int upper) {
  if (upper - lower <= 1) {
    return 0;
  }
  int medium = (lower + upper) >> 1;
  int64_t res = calc(lower, medium) + calc(medium, upper);
  int pnt1, pnt2;
  // Caculates across
  pnt1 = pnt2 = medium;
  ++tag;
  FOR(i, lower, medium) {
    const auto& radio = radios[idxs[i]];
    int lowerF = radio.f - m;
    int upperF = radio.f + m;
    for (; pnt2 < upper && radios[idxs[pnt2]].f <= upperF; ++pnt2) {
      const auto& radio2 = radios[idxs[pnt2]];
      if (radio2.f >= lowerF) {
        tags[pnt2] = tag;
        fen.update(radios[idxs[pnt2]].xIdx, 1);
      }
    }
    for (; pnt1 < pnt2 && radios[idxs[pnt1]].f < lowerF; ++pnt1) {
      if (tags[pnt1] == tag) {
        fen.update(radios[idxs[pnt1]].xIdx, -1);
      }
    }
    res += fen.calcRange(radio.lowerIdx, radio.upperIdx);
  }
  for (; pnt1 < pnt2; ++pnt1) {
    if (tags[pnt1] == tag) {
      fen.update(radios[idxs[pnt1]].xIdx, -1);
    }
  }
  // Merges ordered by frequency
  pnt1 = lower;
  pnt2 = medium;
  int pnt = lower;
  while (pnt1 < medium && pnt2 < upper) {
    tmpIdxs[pnt++] = radios[idxs[pnt1]].f < radios[idxs[pnt2]].f ? idxs[pnt1++] : idxs[pnt2++];
  }
  for (; pnt1 < medium; tmpIdxs[pnt++] = idxs[pnt1++]) {}
  for (; pnt2 < upper; tmpIdxs[pnt++] = idxs[pnt2++]) {}
  FOR(i, lower, upper) {
    idxs[i] = tmpIdxs[i];
  }
  return res;
}

int main() {
  int n;
  io::readInt(n);
  io::readInt(m);
  dis.resize(n);
  FOR(i, 0, n) {
    radios[i].init();
    idxs[i] = i;
    dis[i] = radios[i].x;
  }
  SORTUNIQUE(dis);
  fen.init(SIZE(dis));
  FOR(i, 0, n) {
    auto& radio = radios[i];
    radio.xIdx = INDEX(dis, radio.x);
    radio.lowerIdx = INDEX(dis, radio.x - radio.r);
    radio.upperIdx = INDEX(dis, radio.x + radio.r + 1);
  }
  sort(radios, radios + n);
  io::writeInt(calc(0, n));
  io::writeChar('\n');
  return 0;
}
