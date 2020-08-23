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

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define GET0 get<0>
#define GET1 get<1>
#define GET2 get<2>
#define CASTI64 static_cast<int64_t>

#define CAST static_cast
#define I64 int64_t
#define UI64 uint64_t

#define CASTI32 static_cast<int>

namespace oi {

namespace {

constexpr int kBufferSize = 1 << 15;
char buffer[kBufferSize];
int pos, len;

inline void loadBuffer() {
  len = CASTI32(fread(buffer, sizeof(char), kBufferSize, stdin));
  pos = 0;
}

inline char nextChar(bool advance = true) {
  if (pos >= len) {
    loadBuffer();
  }
  return buffer[advance ? pos++ : pos];
}

} // namespace

template<typename T>
void readInt(T& res) {
  for (; isspace(nextChar(false)); nextChar()) {}
  bool negative = nextChar(false) == '-';
  if (negative) {
    nextChar();
  }
  res = 0;
  for (; isdigit(nextChar(false)); res = res * 10 + (nextChar() - '0')) {}
  if (negative) {
    res = -res;
  }
}

} // namespace oi

#define MAX_UINT_T UI64

namespace math {

namespace {

inline bool isProductOverflow(MAX_UINT_T a, MAX_UINT_T b) {
  if (!a || !b) {
    return false;
  }
  return a > numeric_limits<MAX_UINT_T>::max() / b;
}

inline void
product(MAX_UINT_T a, MAX_UINT_T b, MAX_UINT_T& high, MAX_UINT_T& low) {
  int halfL = numeric_limits<MAX_UINT_T>::digits >> 1;
  MAX_UINT_T halfMask = numeric_limits<MAX_UINT_T>::max() >> halfL;
  MAX_UINT_T aHigh = a >> halfL, aLow = a & halfMask;
  MAX_UINT_T bHigh = b >> halfL, bLow = b & halfMask;
  high = aHigh * bHigh;
  low = aLow * bLow;
  MAX_UINT_T ab = aHigh * bLow, ba = bHigh * aLow;
  high += (ab >> halfL) + (ba >> halfL);
  MAX_UINT_T lowHigh = (low >> halfL) + (ab & halfMask) + (ba & halfMask);
  high += lowHigh >> halfL;
  low = ((lowHigh & halfMask) << halfL) + (low & halfMask);
}

inline int sgn(MAX_UINT_T a, MAX_UINT_T b) {
  return a < b ? -1 : a == b ? 0 : 1;
}

} // namespace

/** sgn(a*b-c*d) */
inline int
sgnUnsignedProduct(MAX_UINT_T a, MAX_UINT_T b, MAX_UINT_T c, MAX_UINT_T d) {
  bool overflowAB = isProductOverflow(a, b);
  bool overflowCD = isProductOverflow(c, d);
  if (overflowAB) {
    if (overflowCD) {
      MAX_UINT_T high1, low1, high2, low2;
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

/** sgn(a*b-c*d) */
template<typename T>
inline int sgnProduct(T a, T b, T c, T d) {
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
      return -sgnUnsignedProduct(-a, b, -c, d);
    } else {
      return -1;
    }
  } else {
    if (c < 0) {
      return 1;
    } else {
      return -sgnUnsignedProduct(a, b, c, d);
    }
  }
}

/** sgn(a/b-c/d) */
template<typename T>
inline int sgnFraction(T a, T b, T c, T d) {
  assert(b && d);
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

} // namespace math

namespace collections {

template<typename T>
class ConvexHullTricksMonoAddQuery {
public:
  inline void initQueryMaxAndIncreasing(bool queryMax_, bool queryIncreasing_) {
    this->queryMax = queryMax_;
    this->queryIncreasing = queryIncreasing_;
    as.clear();
    bs.clear();
    nums.clear();
    dens.clear();
  }

  inline void add(T a, T b) {
    if (as.empty()) {
      as.push_back(a);
      bs.push_back(b);
      return;
    }
    bool addFront =
        (queryMax && a <= as.front()) || (!queryMax && a >= as.front());
    if (topA_(addFront) == a) {
      if ((queryMax && b <= topB_(addFront)) ||
          (!queryMax && b >= topB_(addFront))) {
        return;
      }
      pop_(addFront);
    }
    T num, den;
    while (true) {
      num = b - topB_(addFront);
      den = topA_(addFront) - a;
      if (den < 0) {
        num = -num;
        den = -den;
      }
      if (nums.empty() ||
          (addFront &&
           math::sgnFraction<T>(num, den, nums.front(), dens.front()) < 0) ||
          (!addFront &&
           math::sgnFraction<T>(nums.back(), dens.back(), num, den) < 0)) {
        break;
      }
      pop_(addFront);
    }
    add_(addFront, a, b, num, den);
  }

  inline int queryLineIdx(T x) {
    for (; !nums.empty() &&
           ((queryIncreasing &&
             math::sgnFraction<T>(nums.front(), dens.front(), x, 1) <= 0) ||
            (!queryIncreasing &&
             math::sgnFraction<T>(x, 1, nums.back(), dens.back()) <= 0));
         pop_(queryIncreasing)) {}
    return queryIncreasing ? 0 : static_cast<int>(nums.size());
  }

  inline T query(T x) {
    assert(!as.empty());
    int idx = queryLineIdx(x);
    return as[idx] * x + bs[idx];
  }

  inline void popFront() {
    as.pop_front();
    bs.pop_front();
    if (!nums.empty()) {
      nums.pop_front();
      dens.pop_front();
    }
  }

  inline void popBack() {
    as.pop_back();
    bs.pop_back();
    if (!nums.empty()) {
      nums.pop_back();
      dens.pop_back();
    }
  }

  inline T frontA() {
    return as.front();
  }

  inline T backA() {
    return as.back();
  }

private:
  inline T topA_(bool addFront) {
    return addFront ? frontA() : backA();
  }

  inline T topB_(bool addFront) {
    return addFront ? bs.front() : bs.back();
  }

  inline void pop_(bool addFront) {
    if (addFront) {
      popFront();
    } else {
      popBack();
    }
  }

  inline void add_(bool addFront, T a, T b, T num, T den) {
    if (addFront) {
      as.push_front(a);
      bs.push_front(b);
      nums.push_front(num);
      dens.push_front(den);
    } else {
      as.push_back(a);
      bs.push_back(b);
      nums.push_back(num);
      dens.push_back(den);
    }
  }

  // Whether to maintain max curve (maintain min curve otherwise)
  bool queryMax;
  bool queryIncreasing;
  // y = ax + b
  deque<T> as, bs;
  // joints at x axis
  deque<T> nums, dens;
}; // class ConvexHullTricksMonoAddQuery

} // namespace collections

int n;
vector<tuple<int, int, I64>> rects;
collections::ConvexHullTricksMonoAddQuery<I64> cht;
vector<I64> dps;

int main() {
  oi::readInt(n);
  rects.reserve(n);
  FOR(i, 0, n) {
    int x, y;
    I64 a;
    oi::readInt(x);
    oi::readInt(y);
    oi::readInt(a);
    rects.emplace_back(x, y, a);
  }
  sort(rects.begin(), rects.end());
  int x = GET0(rects[0]);
  int y = GET1(rects[0]);
  I64 res = CASTI64(x) * y - GET2(rects[0]);
  cht.initQueryMaxAndIncreasing(true, false);
  cht.add(-x, res);
  FOR(i, 1, n) {
    x = GET0(rects[i]);
    y = GET1(rects[i]);
    I64 subRes = max(cht.query(y), 0LL) + CASTI64(x) * y - GET2(rects[i]);
    cht.add(-x, subRes);
    res = max(res, subRes);
  }
  printf("%lld\n", res);
  return 0;
}
