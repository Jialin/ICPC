// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_CALC
#define BASE_SPARSE_TABLE_ARRAY_RESERVE
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/base_sparse_table_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

vector<int> delta;

template<int MAXBIT, int MAXN>
struct MaxIndexSparseTableArray final : ds::BaseSparseTableArray<int, MAXBIT, MAXN> {
  inline void combine(const int& leftValue, const int& rightValue, int& res) const override {
    res = delta[leftValue] > delta[rightValue] ? leftValue : rightValue;
  }
};

MaxIndexSparseTableArray<12, 3000> st;

int main() {
  int n;
  io::readInt(n);
  vector<pair<int, int>> as(n);
  vector<int> orders(n);
  FOR(i, 0, n) {
    io::readInt(as[i].first);
    as[i].second = i;
    orders[i] = i;
  }
  SORT(as);
  delta.resize(n);
  delta[0] = as[0].first;
  FOR(i, 1, n) {
    delta[i] = as[i].first - as[i - 1].first;
  }
  st.reserve(n);
  st.init(move(orders));
  tuple<int, int, int> resGaps{0, 0, 0};
  int resX, resY, resZ;
  FOR(x, 1, n) {
    if (delta[n - x] < get<0>(resGaps)) {
      continue;
    }
    for (int y = (x + 1) >> 1; x + y < n && y <= (x << 1); ++y) {
      int minZ = (max(x, y) + 1) >> 1;
      if (x + y + minZ > n) {
        break;
      }
      int maxZ = min(min(x, y) << 1, n - x - y);
      if (minZ > maxZ) {
        continue;
      }
      int zIdx = st.calc(n - x - y - maxZ, n - x - y - minZ + 1);
      auto subResGaps = make_tuple(delta[n - x], delta[n - x - y], delta[zIdx]);
      if (resGaps < subResGaps) {
        resGaps = subResGaps;
        resX = x;
        resY = y;
        resZ = n - zIdx - x - y;
      }
    }
  }
  vector<int> res(n, -1);
  int pnt = n - 1;
  FOR(i, 0, resX) {
    res[as[pnt--].second] = 1;
  }
  FOR(i, 0, resY) {
    res[as[pnt--].second] = 2;
  }
  FOR(i, 0, resZ) {
    res[as[pnt--].second] = 3;
  }
  FOR(i, 0, n) {
    io::writeInt(res[i]);
    io::writeChar(i + 1 == n ? '\n' : ' ');
  }
  return 0;
}
