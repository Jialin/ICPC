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

namespace {

using MaxUInt = uint64_t;
const MaxUInt kMax = numeric_limits<MaxUInt>::max();
const int kHalfL = numeric_limits<MaxUInt>::digits >> 1;
const MaxUInt kHalfMask = kMax >> kHalfL;

inline bool isProductOverflow(MaxUInt a, MaxUInt b) {
  if (!a || !b) {
    return false;
  }
  return a > kMax / b;
}

inline void product(MaxUInt a, MaxUInt b, MaxUInt &high, MaxUInt &low) {
  MaxUInt aHigh = a >> kHalfL, aLow = a & kHalfMask;
  MaxUInt bHigh = b >> kHalfL, bLow = b & kHalfMask;
  high = aHigh * bHigh;
  low = aLow * bLow;
  MaxUInt ab = aHigh * bLow, ba = bHigh * aLow;
  high += (ab >> kHalfL) + (ba >> kHalfL);
  MaxUInt lowHigh = (low >> kHalfL) + (ab & kHalfMask) + (ba & kHalfMask);
  high += lowHigh >> kHalfL;
  low = ((lowHigh & kHalfMask) << kHalfL) + (low & kHalfMask);
}

inline int sgn(MaxUInt a, MaxUInt b) { return a < b ? -1 : a == b ? 0 : 1; }

/** sgn(a*b-c*d) */
inline int sgnUnsignedProduct(MaxUInt a, MaxUInt b, MaxUInt c, MaxUInt d) {
  bool overflowAB = isProductOverflow(a, b);
  bool overflowCD = isProductOverflow(c, d);
  if (overflowAB) {
    if (overflowCD) {
      MaxUInt high1, low1, high2, low2;
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
template <typename T> inline int sgnFraction(T a, T b, T c, T d) {
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
      return -sgnUnsignedProduct(-a, d, -c, b);
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

template <typename T> class Line {
public:
  T a, b;
  mutable T num, den;

  inline Line(T a_, T b_) : a(a_), b(b_), num(0), den(1) {}

  inline bool operator<(const Line<T> &o) const { return a < o.a; }

  inline bool operator<(T x) const {
    return sgnFraction<T>(num, den, x, 1) < 0;
  }
};

} // namespace

template <typename T>
class ConvexHullTricks : public multiset<Line<T>, less<void>> {
public:
  inline void initQueryMax(bool queryMax_) {
    queryMax = queryMax_;
    this->clear();
  }

  inline void add(T a, T b) {
    if (!queryMax) {
      a = -a;
      b = -b;
    }
    auto y = this->emplace(a, b);
    // Remove following lines
    auto z = next(y);
    update(y, z);
    while (!inOrder(y, z)) {
      z = this->erase(z);
      update(y, z);
    }
    // Remove newly added line
    if (y == this->begin()) {
      return;
    }
    auto x = prev(y);
    update(x, y);
    if (!inOrder(x, y)) {
      y = this->erase(y);
      update(x, y);
    }
    // Remove preceeding lines
    for (y = x; x != this->begin() && !inOrder(--x, y); y = x) {
      update(x, this->erase(y));
    }
  }

  inline T query(T x) const {
    assert(!this->empty());
    auto l = this->lower_bound(x);
    T res = l->a * x + l->b;
    return queryMax ? res : -res;
  }

private:
  inline void
  update(const typename multiset<Line<T>, less<void>>::iterator &x,
         const typename multiset<Line<T>, less<void>>::iterator &y) {
    if (y == this->end()) {
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

  inline bool
  inOrder(const typename multiset<Line<T>, less<void>>::iterator &x,
          const typename multiset<Line<T>, less<void>>::iterator &y) const {
    return y == this->end() ||
           sgnFraction<T>(x->num, x->den, y->num, y->den) < 0;
  }

  bool queryMax;
};

} // namespace collections

#define I64 int64_t
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define CLEAR(as, v) memset(as, v, sizeof(as))

const int MAXN = 50000;

int n;
collections::ConvexHullTricks<I64> cht;
int speeds[MAXN];
I64 intercepts[MAXN];

int main() {
  int q;
  io::readInt(n);
  io::readInt(q);
  CLEAR(speeds, 0);
  CLEAR(intercepts, 0);
  cht.initQueryMax(true);
  cht.add(0, 0);
  FOR(_, 0, q) {
    int op, ts;
    io::readInt(op);
    io::readInt(ts);
    if (op == 1) {
      int idx, newSpeed;
      io::readInt(idx);
      io::readInt(newSpeed);
      --idx;
      intercepts[idx] += (speeds[idx] - newSpeed + 0LL) * ts;
      speeds[idx] = newSpeed;
      cht.add(newSpeed, intercepts[idx]);
    } else {
      printf("%lld\n", cht.query(ts));
    }
  }
  return 0;
}
