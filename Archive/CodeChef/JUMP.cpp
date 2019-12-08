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

// @autogen
namespace collections {

namespace {

/** floor(num/den) */
template <typename T> inline T floorDiv(T num, T den) {
  assert(den);
  T res = num / den;
  return (num ^ den) >= 0 ? res : res - static_cast<bool>(num % den);
}

} // namespace

template <typename T> class MinLiChaoTreeKnownQueries {
private:
  class Node {
  public:
    T a, b;
    int leftIdx, rightIdx;

    inline Node(T a_, T b_, int leftIdx_ = -1, int rightIdx_ = -1)
        : a(a_), b(b_), leftIdx(leftIdx_), rightIdx(rightIdx_) {}
  };

  inline int newNode(T a, T b) {
    int size = static_cast<int>(nodes.size());
    nodes.emplace_back(a, b);
    return size;
  }

  int n;
  vector<T> queries;
  vector<Node> nodes;

public:
  inline void init(const vector<T> &orderedUniqueQueries) {
    this->queries = orderedUniqueQueries;
    n = static_cast<int>(orderedUniqueQueries.size());
    int capacity = 1 << (31 - __builtin_clz(n));
    nodes.reserve(capacity << (1 + (capacity < n)));
    reset();
  }

  inline void reset() { nodes.clear(); }

  inline void add(T a, T b) {
    if (nodes.empty()) {
      newNode(a, b);
      return;
    }
    int idx = 0, lower = 0, upper = n;
    while (true) {
      auto &node = nodes[idx];
      if (node.a == a) {
        if (node.b > b) {
          node.b = b;
        }
        break;
      }
      T joint = floorDiv(node.b - b, a - node.a);
      if (joint < queries[lower]) {
        if (node.a > a) {
          node.a = a;
          node.b = b;
        }
        break;
      }
      if (joint >= queries[upper - 1]) {
        if (a > node.a) {
          node.a = a;
          node.b = b;
        }
        break;
      }
      if (lower + 1 >= upper) {
        break;
      }
      int medium = (lower + upper) >> 1;
      if ((joint < queries[medium]) ^ (a > node.a)) {
        swap(node.a, a);
        swap(node.b, b);
      }
      if (joint < queries[medium]) {
        idx = node.leftIdx;
        if (idx < 0) {
          node.leftIdx = newNode(a, b);
          break;
        }
        upper = medium;
      } else {
        idx = node.rightIdx;
        if (idx < 0) {
          node.rightIdx = newNode(a, b);
          break;
        }
        lower = medium;
      }
    }
  }

  inline T query(T x) const {
    assert(!nodes.empty());
    int idx = static_cast<int>(lower_bound(queries.begin(), queries.end(), x) -
                               queries.begin());
    assert(idx < static_cast<int>(queries.size()) && queries[idx] == x);
    return queryIdx(idx);
  }

  inline T queryIdx(int queryIdx) const {
    assert(!nodes.empty());
    T x = queries[queryIdx];
    T res = nodes[0].a * x + nodes[0].b;
    for (int idx = 0, lower = 0, upper = n; idx >= 0;) {
      const auto &node = nodes[idx];
      if (idx) {
        T subRes = node.a * x + node.b;
        if (res > subRes) {
          res = subRes;
        }
      }
      int medium = (lower + upper) >> 1;
      if (medium <= queryIdx) {
        idx = node.rightIdx;
        lower = medium;
      } else {
        idx = node.leftIdx;
        upper = medium;
      }
    }
    return res;
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

int n;
vector<int> as, hs;
vector<I64> hs2;
vector<int> ps;
vector<int> revPs;
vector<int> sortedPs;
vector<int> tmpSortedPs;
vector<int> hsIdx;
collections::MinLiChaoTreeKnownQueries<I64> cht;
vector<I64> sortedHs;
vector<I64> dps;
constexpr int64_t kMaxI64 = numeric_limits<int64_t>::max();

inline void dfs(int lower, int upper) {
  if (lower + 1 == upper) {
    return;
  }
  int medium = (lower + upper) >> 1;
  for (int i = lower, j = medium, k = lower; k < upper; ++k) {
    int v = sortedPs[k];
    tmpSortedPs[v < medium ? i++ : j++] = v;
  }
  copy(tmpSortedPs.begin() + lower, tmpSortedPs.begin() + upper,
       sortedPs.begin() + lower);
  dfs(lower, medium);
  // ===
  cht.reset();
  int i, j;
  for (i = lower, j = medium; i < medium && j < upper;) {
    int idxI = revPs[sortedPs[i]];
    int idxJ = revPs[sortedPs[j]];
    if (idxI < idxJ) {
      cht.add(-(hs[idxI] << 1), dps[idxI] + hs2[idxI]);
      ++i;
    } else {
      if (i != lower) {
        dps[idxJ] =
            min(dps[idxJ], as[idxJ] + hs2[idxJ] + cht.queryIdx(hsIdx[idxJ]));
      }
      ++j;
    }
  }
  for (; j < upper; ++j) {
    int idxJ = revPs[sortedPs[j]];
    dps[idxJ] =
        min(dps[idxJ], as[idxJ] + hs2[idxJ] + cht.queryIdx(hsIdx[idxJ]));
  }
  dfs(medium, upper);
  // ===
  int idx;
  for (i = lower, j = medium, idx = lower; i < medium && j < upper;) {
    if (revPs[sortedPs[i]] < revPs[sortedPs[j]]) {
      tmpSortedPs[idx++] = sortedPs[i++];
    } else {
      tmpSortedPs[idx++] = sortedPs[j++];
    }
  }
  for (; i < medium; ++i) {
    tmpSortedPs[idx++] = sortedPs[i];
  }
  for (; j < upper; ++j) {
    tmpSortedPs[idx++] = sortedPs[j];
  }
  copy(tmpSortedPs.begin() + lower, tmpSortedPs.begin() + upper,
       sortedPs.begin() + lower);
}

int main() {
  io::readInt(n);
  ps.resize(n);
  revPs.resize(n);
  tmpSortedPs.resize(n);
  FOR(i, 0, n) {
    io::readInt(ps[i]);
    revPs[--ps[i]] = i;
  }
  sortedPs = ps;
  as.resize(n);
  FOR(i, 0, n) { io::readInt(as[i]); }
  hs.resize(n);
  hs2.resize(n);
  sortedHs.resize(n);
  FOR(i, 0, n) {
    int h;
    io::readInt(h);
    hs[i] = h;
    sortedHs[i] = h;
    hs2[i] = sqr<I64>(hs[i]);
  }
  SORTUNIQUE(sortedHs);
  hsIdx.resize(n);
  FOR(i, 0, n) { hsIdx[i] = INDEX(sortedHs, hs[i]); }
  cht.init(sortedHs);
  dps.assign(n, kMaxI64);
  dps[0] = as[0];
  dfs(0, n);
  printf("%lld\n", dps[n - 1]);
  return 0;
}
