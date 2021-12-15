// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_CALC
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/base_sparse_table_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000009;

vector<pair<int, int>> positions;

template<int MAXBIT, int MAXN>
struct MaxIndexSparseTableArray final : ds::BaseSparseTableArray<int, MAXBIT, MAXN> {
  using V = int;

  inline void combine(const V& lv, const V& rv, V& res) const override {
    res = positions[lv].second > positions[rv].second ? lv : rv;
  }
};

const int MAXN = 100000;
const int MAXM = MAXN << 1;

MaxIndexSparseTableArray<17, 100000> st;

int pnt;
int results[MAXM], unused[MAXM];
int leftIdxs[MAXM], rightIdxs[MAXM], mediums[MAXM];

inline int getResult(int idx) {
  return idx >= 0 ? results[idx] : 0;
}

inline int getUnused(int idx) {
  return idx >= 0 ? unused[idx] : -1;
}

inline void merge(int lIdx, int rIdx, int idx) {
  unused[idx] = getResult(lIdx) + getResult(rIdx);
  results[idx] = max(
      max(getResult(lIdx) + getUnused(rIdx), getUnused(lIdx) + getResult(rIdx)) + 1, unused[idx]);
}

inline int init(int lower, int upper) {
  if (lower >= upper) {
    return -1;
  }
  int medium = st.calc(lower, upper);
  int idx = pnt++;
  mediums[idx] = medium;
  leftIdxs[idx] = init(lower, medium);
  rightIdxs[idx] = init(medium + 1, upper);
  merge(leftIdxs[idx], rightIdxs[idx], idx);
  return idx;
}

int L, R;

inline pair<int, int> calc(int idx, int lower, int upper) {
  if (idx < 0 || R <= positions[lower].first || positions[upper - 1].first < L) {
    return {0, -1};
  }
  // DEBUGF(
  //     "idx:%d [%d,%d) [%d,%d] L:%d R:%d\n",
  //     idx,
  //     lower,
  //     upper,
  //     positions[lower].first,
  //     positions[upper - 1].first,
  //     L,
  //     R);
  if (L <= positions[lower].first && positions[upper - 1].first < R) {
    // DEBUGF(
    //     "!!!! covered [%d,%d) [%d,%d] L:%d R:%d: %d, %d\n",
    //     lower,
    //     upper,
    //     positions[lower].first,
    //     positions[upper - 1].first,
    //     L,
    //     R,
    //     results[idx],
    //     unused[idx]);
    return {results[idx], unused[idx]};
  }
  int mediumX = positions[mediums[idx]].first;
  if (R <= mediumX) {
    return calc(leftIdxs[idx], lower, mediums[idx]);
  } else if (mediumX < L) {
    return calc(rightIdxs[idx], mediums[idx] + 1, upper);
  }
  auto lv = calc(leftIdxs[idx], lower, mediums[idx]);
  auto rv = calc(rightIdxs[idx], mediums[idx] + 1, upper);
  // DEBUGF(
  //     "!!!! [%d,%d) [%d,%d] L:%d R:%d: %d, %d\n",
  //     lower,
  //     upper,
  //     positions[lower].first,
  //     positions[upper - 1].first,
  //     L,
  //     R,
  //     max(max(lv.first + rv.second, lv.second + rv.first) + 1, lv.first + rv.first),
  //     lv.first + rv.first);
  return {
      max(max(lv.first + rv.second, lv.second + rv.first) + 1, lv.first + rv.first),
      lv.first + rv.first};
}

int main() {
  int n, k;
  io::readInt(n);
  io::readInt(k);
  positions.reserve(n);
  int lastX, lastY;
  FOR(i, 0, k) {
    io::readInt(lastX);
    io::readInt(lastY);
    positions.emplace_back(lastX, lastY);
  }
  int a, b, c, d;
  io::readInt(a);
  io::readInt(b);
  io::readInt(c);
  io::readInt(d);
  FOR(i, k, n) {
    int x = (a * (lastX + 0LL) + b) % MOD;
    int y = (c * (lastY + 0LL) + d) % MOD;
    positions.emplace_back(x, y);
    lastX = x;
    lastY = y;
  }
  sort(ALL(positions), [](const auto& x, const auto& y) {
    return x.first < y.first;
  });
  vector<int> idxs(n);
  FOR(i, 0, n) {
    idxs[i] = i;
  }
  st.init(move(idxs));
  // DEBUGF("init start\n");
  pnt = 0;
  init(0, n);
  // DEBUGF("init end pnt:%d\n", pnt);
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    io::readInt(L);
    io::readInt(R);
    ++R;
    io::writeInt(calc(0, 0, n).first);
    io::writeChar('\n');
  }
  return 0;
}
