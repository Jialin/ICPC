#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

namespace io {

namespace {

constexpr int kBufferSize = 1 << 15;
char buffer[kBufferSize];
int pos, len;
bool ended = false;

inline void loadBuffer() {
  len = static_cast<int>(fread(buffer, sizeof(char), kBufferSize, stdin));
  pos = 0;
}

inline char nextChar(bool advance = true) {
  if (ended) {
    return 0;
  }
  if (pos >= len) {
    loadBuffer();
    if (len == 0) {
      ended = true;
      return 0;
    }
  }
  return buffer[advance ? pos++ : pos];
}

} // namespace

template <typename T> void readInt(T &res) {
  for (; isspace(nextChar(false)); nextChar()) {
  }
  bool negative = nextChar(false) == '-';
  if (negative) {
    nextChar();
  }
  res = 0;
  for (; isdigit(nextChar(false)); res = res * 10 + (nextChar() - '0')) {
  }
  if (negative) {
    res = -res;
  }
}

} // namespace io

namespace collections {

template <typename T> class LiChaoTree {
public:
  inline void initQueryMax(bool queryMax_,
                           const vector<T> &orderedUniqueQueries) {
    this->queries = orderedUniqueQueries;
    queryMax = queryMax_;
    n = static_cast<int>(orderedUniqueQueries.size());
    assert(n);
    capacity = 1 << (31 - __builtin_clz(n));
    capacity <<= 1 + (capacity < n);
    refresh();
  }

  inline void refresh() {
    as.resize(capacity);
    bs.resize(capacity);
    touched.assign(capacity, false);
  }

  inline void add(T a, T b) {
    if (!queryMax) {
      a = -a;
      b = -b;
    }
    int idx = 1, lower = 0, upper = n;
    do {
      if (!touched[idx]) {
        as[idx] = a;
        bs[idx] = b;
        touched[idx] = true;
        break;
      }
      bool lowerAbove = isAbove(a, b, as[idx], bs[idx], queries[lower]);
      bool upperAbove = isAbove(a, b, as[idx], bs[idx], queries[upper - 1]);
      if (!(lowerAbove ^ upperAbove)) {
        if (lowerAbove) {
          as[idx] = a;
          bs[idx] = b;
        }
        break;
      }
      int medium = (lower + upper) >> 1;
      bool mediumAbove = isAbove(a, b, as[idx], bs[idx], queries[medium]);
      if (mediumAbove) {
        swap(as[idx], a);
        swap(bs[idx], b);
      }
      idx <<= 1;
      if (lowerAbove ^ mediumAbove) {
        upper = medium;
      } else {
        idx |= 1;
        lower = medium;
      }
    } while (lower + 1 < upper);
  }

  inline T query(T x) const {
    int idx = static_cast<int>(lower_bound(queries.begin(), queries.end(), x) -
                               queries.begin());
    assert(idx < static_cast<int>(queries.size()) && queries[idx] == x);
    return queryIdx(idx);
  }

  inline T queryIdx(int queryIdx) {
    assert(touched[1]);
    T x = queries[queryIdx];
    T res = as[1] * x + bs[1];
    int idx = 1, lower = 0, upper = n;
    do {
      if (idx > 1 && touched[idx]) {
        res = max(res, as[idx] * x + bs[idx]);
      }
      idx <<= 1;
      int medium = (lower + upper) >> 1;
      if (medium <= queryIdx) {
        idx |= 1;
        lower = medium;
      } else {
        upper = medium;
      }
    } while (lower + 1 < upper);
    return queryMax ? res : -res;
  }

private:
  bool queryMax;
  vector<T> queries;
  int n, capacity;
  // Convex hull lines of the interval
  vector<T> as, bs;
  vector<bool> touched;

  inline bool isAbove(T a1, T b1, T a2, T b2, T x) {
    return (a1 - a2) * x > b2 - b1;
  }
};

} // namespace collections

#define I64 int64_t
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define SORTUNIQUE(vs)                                                         \
  sort(vs.begin(), vs.end());                                                  \
  vs.erase(unique(vs.begin(), vs.end()), vs.end())
#define INDEX(idx, v)                                                          \
  static_cast<int>(lower_bound(idx.begin(), idx.end(), v) - idx.begin())

template <typename T> inline T sqr(T x) { return x * x; }

int n, k;
vector<int> a;
vector<int> aIdx;
vector<I64> sortedA;
vector<I64> dp, nextDp;
collections::LiChaoTree<I64> lct;

int main() {
  io::readInt(n);
  io::readInt(k);
  a.resize(n);
  dp.resize(n);
  sortedA.resize(n);
  FOR(i, 0, n) {
    io::readInt(a[i]);
    dp[i] = sqr<I64>(a[i] - a[0]);
    sortedA[i] = a[i];
  }
  SORTUNIQUE(sortedA);
  aIdx.resize(n);
  FOR(i, 0, n) { aIdx[i] = INDEX(sortedA, a[i]); }
  lct.initQueryMax(false, sortedA);
  nextDp.resize(n);
  FOR(i, 1, k) {
    lct.refresh();
    lct.add(-(a[i] << 1), dp[i - 1] + sqr<I64>(a[i]));
    FOR(j, i, n) {
      nextDp[j] = sqr<I64>(a[j]) + lct.queryIdx(aIdx[j]);
      if (j + 1 < n) {
        lct.add(-(a[j + 1] << 1), dp[j] + sqr<I64>(a[j + 1]));
      }
    }
    dp.swap(nextDp);
  }
  printf("%lld\n", dp[n - 1]);
  return 0;
}
