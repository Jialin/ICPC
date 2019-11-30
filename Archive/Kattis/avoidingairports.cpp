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

template <typename T> class Vector2D {
public:
  inline void init(int n, int m = -1) {
    lastOut.assign(n, -1);
    nxtOut.clear();
    values.clear();
    if (m > 0) {
      nxtOut.reserve(m);
      values.reserve(m);
    }
  }

  inline void add(int x, T v) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    lastOut[x] = edgeIdx;
    values.push_back(v);
  }

  vector<int> lastOut, nxtOut;
  vector<T> values;
};

} // namespace collections

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

template <typename T> class MinConvexHullTricksAddDecreasingQueryIncreasing {
private:
  class Line {
  public:
    T a, b, x;

    inline Line(T a_, T b_) : a(a_), b(b_), x(0) {}
  };

  inline void pushBack(T a, T b) {
    lines.emplace_back(a, b);
    ++tail;
  }

  inline void popBack() {
    lines.pop_back();
    --tail;
  }

  vector<Line> lines;
  int head, tail;

public:
  inline void init(int n = -1) {
    lines.clear();
    head = 0;
    tail = 0;
    if (n > 0) {
      lines.reserve(n);
    }
  }

  inline void add(T a, T b) {
    if (empty()) {
      pushBack(a, b);
      return;
    }
    const auto &cl = lines.back();
    if (cl.a == a) {
      if (cl.b <= b) {
        return;
      }
      popBack();
    }
    T x;
    while (true) {
      const auto &l = lines.back();
      x = floorDiv(b - l.b, l.a - a);
      if (head + 1 >= tail || lines[tail - 2].x < x) {
        break;
      }
      popBack();
    }
    if (!empty()) {
      auto &l = lines.back();
      l.x = x;
    }
    pushBack(a, b);
  }

  inline int queryLineIdx(T x) {
    for (; head + 1 < tail && x > lines[head].x; ++head) {
    }
    return head;
  }

  inline T query(T x) {
    assert(!empty());
    const auto &l = lines[queryLineIdx(x)];
    return l.a * x + l.b;
  }

  inline bool empty() const { return head >= tail; }
};

} // namespace collections

struct Edge {
  int from, to, startT, endT;
  inline Edge(int from_, int to_, int startT_, int endT_)
      : from(from_), to(to_), startT(startT_), endT(endT_) {}
};

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define SORTALLBY(vs, clause)                                                  \
  sort(vs.begin(), vs.end(),                                                   \
       [](const decltype(vs)::value_type &a,                                   \
          const decltype(vs)::value_type &b) { return clause; })
#define I64 int64_t

template <typename T> inline T sqr(T x) { return x * x; }

const I64 INF = numeric_limits<I64>::max();

int n, m;
vector<Edge> edges;
vector<int> byS, byE;
collections::Vector2D<int> edgeIdxsByE;
vector<collections::MinConvexHullTricksAddDecreasingQueryIncreasing<I64>> chts;
vector<int> lastOut;
vector<I64> dps;

inline I64 calc() {
  if (n == 1) {
    return 0;
  }
  I64 res = INF;
  for (auto edgeIdx : byS) {
    const auto &edge = edges[edgeIdx];
    while (true) {
      auto &lastOutR = edgeIdxsByE.lastOut[edge.from];
      if (lastOutR < 0) {
        break;
      }
      auto edgeIdxToAdd = edgeIdxsByE.values[lastOutR];
      const auto &edgeToAdd = edges[edgeIdxToAdd];
      if (edgeToAdd.endT >= edge.startT) {
        break;
      }
      lastOutR = edgeIdxsByE.nxtOut[lastOutR];
      if (dps[edgeIdxToAdd] == INF) {
        continue;
      }
      chts[edgeToAdd.to].add(-(edgeToAdd.endT << 1),
                             dps[edgeIdxToAdd] + sqr<I64>(edgeToAdd.endT));
    }
    I64 &subRes = dps[edgeIdx];
    auto &cht = chts[edge.from];
    if (!cht.empty()) {
      subRes = cht.query(edge.startT);
    }
    if (subRes != INF) {
      subRes += sqr<I64>(edge.startT);
    }
    if (!edge.from) {
      subRes = min(subRes, sqr<I64>(edge.startT));
    }
    if (edge.to + 1 == n) {
      res = min(res, subRes);
    }
  }
  return res;
}

int main() {
  io::readInt(n);
  io::readInt(m);
  chts.resize(n);
  edges.reserve(m);
  byS.resize(m);
  byE.resize(m);
  dps.assign(m, INF);
  FOR(i, 0, m) {
    int from, to, startT, endT;
    io::readInt(from);
    io::readInt(to);
    io::readInt(startT);
    io::readInt(endT);
    --from;
    --to;
    edges.emplace_back(from, to, startT, endT);
    byS[i] = i;
    byE[i] = i;
  }
  SORTALLBY(byS, edges[a].startT < edges[b].startT);
  SORTALLBY(byE, edges[a].endT > edges[b].endT);
  edgeIdxsByE.init(n, m);
  for (int edgeIdx : byE) {
    edgeIdxsByE.add(edges[edgeIdx].to, edgeIdx);
  }
  printf("%lld\n", calc());
  return 0;
}
