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

#define FILL(vs, v) fill(vs.begin(), vs.end(), v)
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define CLEAR(as, v) memset(as, v, sizeof(as))

namespace constants {

const int POW10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
};

} // namespace constants

namespace math {

template <typename T> inline int countDigits(T x) {
  int res = 1;
  for (x /= 10; x > 0; x /= 10, ++res) {
  }
  return res;
}

} // namespace math

namespace math {

template <typename T> inline int calcDigit(T x, int idx) {
  return x / constants::POW10[idx] % 10;
}

} // namespace math

namespace collections {

template <typename T, typename OFFSET = int> class ShiftedVector {
public:
  inline void init(OFFSET lowerBound, OFFSET upperBound, T v) {
    vs_.resize(upperBound - lowerBound);
    FILL(vs_, v);
    offset_ = lowerBound;
  }

  inline T &operator[](OFFSET x) { return vs_[x - offset_]; }

private:
  OFFSET offset_;
  vector<T> vs_;
};

} // namespace collections

collections::ShiftedVector<int> priorCnt[9];

inline int calcPrior(int remL, int prior) {
  if (!remL) {
    return prior == 1 ? 1 : 0;
  }
  int &res = priorCnt[remL][prior];
  if (res >= 0) {
    return res;
  }
  res = 0;
  if (remL & 1) {
    FOR(digit, 0, 10) { res += calcPrior(remL - 1, prior - digit); }
  } else {
    FOR(digit, 0, 10) { res += calcPrior(remL - 1, prior + digit); }
  }
  return res;
}

int wholeCnt[9];

inline int calcWhole(int len) {
  int &res = wholeCnt[len];
  if (res >= 0) {
    return res;
  }
  res = 0;
  if (len & 1) {
    FOR(digit, 1, 10) { res += calcPrior(len - 1, -digit); }
  } else {
    FOR(digit, 1, 10) { res += calcPrior(len - 1, digit); }
  }
  return res;
}

inline int calc(int x) {
  int len = math::countDigits(x);
  int res = 0;
  FOR(i, 1, len) { res += calcWhole(i); }
  int prior = 0;
  for (int i = len; i > 0; --i) {
    int digit = math::calcDigit(x, i - 1);
    if (i & 1) {
      FOR(j, i == len ? 1 : 0, digit) { res += calcPrior(i - 1, prior - j); }
      prior -= digit;
    } else {
      FOR(j, i == len ? 1 : 0, digit) { res += calcPrior(i - 1, prior + j); }
      prior += digit;
    }
  }
  return res + (prior == 1);
}

int main() {
  FOR(len, 1, 9) { priorCnt[len].init(-45, 46, -1); }
  CLEAR(wholeCnt, 0xFF);
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", calc(b) - (a ? calc(a - 1) : 0));
  }
  return 0;
}
