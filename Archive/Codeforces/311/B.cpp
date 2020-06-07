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
    if (head >= tail) {
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
    if (head < tail) {
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
    assert(head < tail);
    const auto &l = lines[queryLineIdx(x)];
    return l.a * x + l.b;
  }
};

} // namespace collections

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define SORT(vs) sort(vs.begin(), vs.end())
#define I64 int64_t

int n, m, p;
vector<int> xs;
vector<int> vs;
vector<I64> psvs;
vector<I64> dps;
collections::MinConvexHullTricksAddDecreasingQueryIncreasing<I64> cht;

int main() {
  io::readInt(n);
  io::readInt(m);
  io::readInt(p);
  xs.resize(n);
  FOR(i, 1, n) {
    int d;
    io::readInt(d);
    xs[i] = xs[i - 1] + d;
  }
  vs.resize(m);
  FOR(i, 0, m) {
    int h, t;
    io::readInt(h);
    io::readInt(t);
    vs[i] = t - xs[h - 1];
  }
  SORT(vs);
  psvs.resize(m);
  FOR(i, 0, m) { psvs[i] = (i > 0 ? psvs[i - 1] : 0) + vs[i]; }
  dps.resize(m);
  FOR(i, 0, m) { dps[i] = vs[i] * (i + 1LL) - psvs[i]; }
  FOR(_, 1, p) {
    cht.init(m);
    FOR(i, 0, m) {
      cht.add(-i, dps[i] + psvs[i]);
      dps[i] = vs[i] * (i + 0LL) - psvs[i] + cht.query(vs[i]);
    }
  }
  printf("%lld\n", dps[m - 1]);
  return 0;
}
