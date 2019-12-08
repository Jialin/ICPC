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

/** floor(num/den) */
template <typename T> inline T floorDiv(T num, T den) {
  assert(den);
  T res = num / den;
  return (num ^ den) >= 0 ? res : res - static_cast<bool>(num % den);
}

} // namespace

template <typename T> class MinConvexHullTricks {
private:
  class Line {
  public:
    T a, b;
    mutable T x;

    inline Line(T a_, T b_) : a(a_), b(b_), x(0) {}

    inline bool operator<(const Line &o) const { return a > o.a; }

    inline bool operator<(T x_) const { return x < x_; }
  };

  using Iterator = typename multiset<Line, less<>>::iterator;

  multiset<Line, less<>> lines_;

  inline void update(const Iterator &x, const Iterator &y) {
    const static T kMax = numeric_limits<T>::max();
    const static T kMin = numeric_limits<T>::min();
    if (y == lines_.end()) {
      x->x = kMax;
    } else if (x->a == y->a) {
      x->x = x->b < y->b ? kMax : kMin;
    } else {
      x->x = floorDiv(y->b - x->b, x->a - y->a);
    }
  }

  inline bool inOrder(const Iterator &x, const Iterator &y) const {
    return y == lines_.end() || x->x < y->x;
  }

public:
  inline void init() { lines_.clear(); }

  inline void add(T a, T b) {
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
    return l->a * x + l->b;
  }

  inline int size() { return static_cast<int>(lines_.size()); }

  inline bool empty() { return lines_.empty(); }

  inline const multiset<Line, less<>> &lines() const { return lines_; }
};

} // namespace collections

#define I64 int64_t
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename T> inline T sqr(T x) { return x * x; }

constexpr int64_t kMaxI64 = numeric_limits<int64_t>::max();

namespace collections {

class BinaryIndexedTree {
private:
  int n;

public:
  inline void init(int n_) { n = n_; }

  inline void update(int idx, const function<void(int)> &updater) {
    for (; idx < n; idx |= idx + 1) {
      updater(idx);
    }
  }

  inline void query(int idx, const function<void(int)> &queryProcessor) {
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
      queryProcessor(idx);
    }
  }
};
} // namespace collections

// f_i = A_i + min(f_j + (H_i - H_j)^2, j < i)
// f_i = A_i+H_i^2+min(f_j+H_j^2+(-2*H_j)*H_i)

vector<collections::MinConvexHullTricks<I64>> chts;

int n;
vector<int> as, hs;
vector<I64> hs2;
vector<int> revP;
collections::BinaryIndexedTree bit;

inline I64 calc() {
  I64 res = kMaxI64;
  chts.resize(n);
  bit.init(n);
  for (int idx : revP) {
    if (!idx) {
      res = as[idx];
    } else {
      bit.query(idx, [&res](int idx) { res = });
      res = as[idx] + hs2[idx] + bit.calc(idx, hs[idx]);
    }
    bit.update(idx, -(hs[idx] << 1), res + hs2[idx]);
  }
  return res;
}

int main() {
  io::readInt(n);
  revP.resize(n);
  FOR(i, 0, n) {
    int p;
    io::readInt(p);
    revP[p - 1] = i;
  }
  as.resize(n);
  FOR(i, 0, n) { io::readInt(as[i]); }
  hs.resize(n);
  hs2.resize(n);
  FOR(i, 0, n) {
    io::readInt(hs[i]);
    hs2[i] = sqr<I64>(hs[i]);
  }
  printf("%lld\n", calc());
  return 0;
}
