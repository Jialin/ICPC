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

using LL = long long;

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define CLEAR(as, v) memset(as, v, sizeof(as))
#define CAST static_cast

namespace constants {

const LL POW10[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000,
    100000000000,
    1000000000000,
    10000000000000,
    100000000000000,
    1000000000000000,
    10000000000000000,
    100000000000000000,
    1000000000000000000,
};

} // namespace constants

namespace math {

inline int countDigits(LL x) {
  int res = 1;
  for (x /= 10; x > 0; x /= 10, ++res) {
  }
  return res;
}

} // namespace math

inline LL calcCnt(int l) { return constants::POW10[l]; }

LL sum[19];

inline LL calcSum(int l) {
  if (sum[l] >= 0) {
    return sum[l];
  }
  if (l == 0) {
    return sum[l] = 0;
  }
  return sum[l] = calcSum(l - 1) * 10 + calcCnt(l - 1) * 45;
}

inline LL calcSumNonZero(int l) {
  if (l == 0) {
    return 0;
  }
  return calcSum(l - 1) * 9 + calcCnt(l - 1) * 45;
}

inline LL calc(LL x) {
  int length = math::countDigits(x);
  LL res = 0;
  FOR(i, 1, length) { res += calcSumNonZero(i); }
  for (int i = length; i > 0; --i) {
    LL pow10 = constants::POW10[i - 1];
    int digit = CAST<int>(x / pow10);
    x %= pow10;
    res += (digit - 1 + (i != length)) * calcSum(i - 1);
    res += (digit - 1) * digit / 2 * calcCnt(i - 1);
    res += digit * (x + 1);
  }
  return res;
}

int main() {
  CLEAR(sum, 0xFF);
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    LL a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", calc(b) - (a ? calc(a - 1) : 0));
  }
  return 0;
}
