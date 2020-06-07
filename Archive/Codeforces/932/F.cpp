#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
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

namespace graphs {

class UnweightedGraph {
public:
  inline void init(int n_, int m = -1) {
    this->n = n_;
    lastOut.assign(n, -1);
    inDegree.assign(n, 0);
    outDegree.assign(n, 0);
    if (m >= 0) {
      nxtOut.reserve(m);
      toIdx.reserve(m);
    }
    nxtOut.clear();
    toIdx.clear();
  }

  inline void addDirected(int u, int v) {
    int edgeIdx = edgeCnt();
    nxtOut.push_back(lastOut[u]);
    toIdx.push_back(v);
    lastOut[u] = edgeIdx;
    ++inDegree[v];
    ++outDegree[u];
  }

  inline void addUndirected(int u, int v) {
    addDirected(u, v);
    addDirected(v, u);
  }

  inline void outEdges(int u,
                       const function<void(int)> &edgeIdxProcessor) const {
    for (int edgeIdx = lastOut[u]; edgeIdx >= 0; edgeIdx = nxtOut[edgeIdx]) {
      edgeIdxProcessor(edgeIdx);
    }
  }

  inline int edgeCnt() const { return static_cast<int>(toIdx.size()); }

  int n;
  vector<int> lastOut, inDegree, outDegree;
  vector<int> nxtOut, toIdx;
};

} // namespace graphs

namespace collections {

template <typename T, typename CMP_UINT_T = uint64_t> class ConvexHullTricks {
public:
  inline void initQueryMax(bool queryMax_) {
    queryMax = queryMax_;
    lines_.clear();
  }

  inline void add(T a, T b) {
    if (!queryMax) {
      a = -a;
      b = -b;
    }
    auto y = lines_.emplace(a, b);
    // Remove following lines
    auto z = next(y);
    update(y, z);
    while (!inOrder(y, z)) {
      z = lines_.erase(z);
      update(y, z);
    }
    // Remove newly added line
    if (y == lines_.begin()) {
      return;
    }
    auto x = prev(y);
    update(x, y);
    if (!inOrder(x, y)) {
      y = lines_.erase(y);
      update(x, y);
    }
    // Remove preceeding lines
    for (y = x; x != lines_.begin() && !inOrder(--x, y); y = x) {
      update(x, lines_.erase(y));
    }
  }

  inline T query(T x) const {
    assert(!lines_.empty());
    auto l = lines_.lower_bound(x);
    T res = l->a * x + l->b;
    return queryMax ? res : -res;
  }

  inline int size() { return static_cast<int>(lines_.size()); }

  inline void lines(const function<void(T, T)> &lineProcessor) {
    for (const Line &line : lines_) {
      if (queryMax) {
        lineProcessor(line.a, line.b);
      } else {
        lineProcessor(-line.a, -line.b);
      }
    }
  }

private:
  class Line {
  public:
    T a, b;
    mutable T num, den;

    inline Line(T a_, T b_) : a(a_), b(b_), num(0), den(1) {}

    inline bool operator<(const Line &o) const { return a < o.a; }

    inline bool operator<(T x) const { return sgnFraction(num, den, x, 1) < 0; }
  };

  using Iterator = typename multiset<Line, less<>>::iterator;

  bool queryMax;
  multiset<Line, less<>> lines_;

  inline void update(const Iterator &x, const Iterator &y) {
    if (y == lines_.end()) {
      x->num = 1;
      x->den = 0;
    } else if (x->a == y->a) {
      x->num = x->b > y->b ? 1 : -1;
      x->den = 0;
    } else {
      x->num = y->b - x->b;
      x->den = x->a - y->a;
    }
  }

  inline bool inOrder(const Iterator &x, const Iterator &y) const {
    return y == lines_.end() || sgnFraction(x->num, x->den, y->num, y->den) < 0;
  }

  static const CMP_UINT_T kMax = numeric_limits<CMP_UINT_T>::max();
  static const int kHalfL = numeric_limits<CMP_UINT_T>::digits >> 1;
  static const CMP_UINT_T kHalfMask = kMax >> kHalfL;

  inline static bool isProductOverflow(CMP_UINT_T a, CMP_UINT_T b) {
    if (!a || !b) {
      return false;
    }
    return a > kMax / b;
  }

  inline static void product(CMP_UINT_T a, CMP_UINT_T b, CMP_UINT_T &high,
                             CMP_UINT_T &low) {
    CMP_UINT_T aHigh = a >> kHalfL, aLow = a & kHalfMask;
    CMP_UINT_T bHigh = b >> kHalfL, bLow = b & kHalfMask;
    high = aHigh * bHigh;
    low = aLow * bLow;
    CMP_UINT_T ab = aHigh * bLow, ba = bHigh * aLow;
    high += (ab >> kHalfL) + (ba >> kHalfL);
    CMP_UINT_T lowHigh = (low >> kHalfL) + (ab & kHalfMask) + (ba & kHalfMask);
    high += lowHigh >> kHalfL;
    low = ((lowHigh & kHalfMask) << kHalfL) + (low & kHalfMask);
  }

  inline static int sgn(CMP_UINT_T a, CMP_UINT_T b) {
    return a < b ? -1 : a == b ? 0 : 1;
  }

  /** sgn(a*b-c*d) */
  inline static int sgnUnsignedProduct(CMP_UINT_T a, CMP_UINT_T b, CMP_UINT_T c,
                                       CMP_UINT_T d) {
    bool overflowAB = isProductOverflow(a, b);
    bool overflowCD = isProductOverflow(c, d);
    if (overflowAB) {
      if (overflowCD) {
        CMP_UINT_T high1, low1, high2, low2;
        product(a, b, high1, low1);
        product(c, d, high2, low2);
        int sgnHigh = sgn(high1, high2);
        return sgnHigh ? sgnHigh : sgn(low1, low2);
      } else {
        return 1;
      }
    } else {
      if (overflowCD) {
        return -1;
      } else {
        return sgn(a * b, c * d);
      }
    }
  }

  /** sgn(a/b-c/d) */
  inline static int sgnFraction(T a, T b, T c, T d) {
    if (b < 0) {
      a = -a;
      b = -b;
    }
    if (d < 0) {
      c = -c;
      d = -d;
    }
    if (a < 0) {
      if (c < 0) {
        return sgnUnsignedProduct(-c, b, -a, d);
      } else {
        return -1;
      }
    } else {
      if (c < 0) {
        return 1;
      } else {
        return sgnUnsignedProduct(a, d, c, b);
      }
    }
  }
};

} // namespace collections

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define I64 int64_t
#define CASTI32 static_cast<int>

int n;
vector<int> as, bs;
vector<int> nodeCnts;
graphs::UnweightedGraph tree;
vector<I64> dps;
vector<collections::ConvexHullTricks<I64> *> chts;

inline void dfsDP(int u, int parent) {
  nodeCnts[u] = 1;
  int maxLineCntIdx = -1, maxLineCnt;
  tree.outEdges(u, [u, parent, &maxLineCntIdx, &maxLineCnt](int edgeIdx) {
    int v = tree.toIdx[edgeIdx];
    if (parent == v) {
      return;
    }
    dfsDP(v, u);
    nodeCnts[u] += nodeCnts[v];
    if (maxLineCntIdx < 0 || maxLineCnt < CASTI32(chts[v]->size())) {
      maxLineCnt = CASTI32(chts[v]->size());
      maxLineCntIdx = v;
    }
  });
  if (maxLineCntIdx < 0) {
    chts[u] = new collections::ConvexHullTricks<I64>();
    chts[u]->initQueryMax(false);
    dps[u] = 0;
  } else {
    chts[u] = chts[maxLineCntIdx];
    tree.outEdges(u, [u, parent, maxLineCntIdx](int edgeIdx) {
      int v = tree.toIdx[edgeIdx];
      if (parent == v || maxLineCntIdx == v) {
        return;
      }
      chts[v]->lines([u](I64 a, I64 b) { chts[u]->add(a, b); });
    });
    dps[u] = chts[u]->query(as[u]);
  }
  chts[u]->add(bs[u], dps[u]);
}

int main() {
  io::readInt(n);
  as.resize(n);
  bs.resize(n);
  FOR(i, 0, n) { io::readInt(as[i]); }
  FOR(i, 0, n) { io::readInt(bs[i]); }
  tree.init(n, n << 1);
  FOR(_, 1, n) {
    int x, y;
    io::readInt(x);
    io::readInt(y);
    tree.addUndirected(x - 1, y - 1);
  }
  dps.resize(n);
  nodeCnts.resize(n);
  chts.resize(n);
  dfsDP(0, -1);
  FOR(i, 0, n) { printf("%lld%c", dps[i], i + 1 == n ? '\n' : ' '); }
  return 0;
}
