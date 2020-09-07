#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#include "debug/debug.h"
#include "math/fib/fib_power_sum.h"
#include "math/mod/stirling_first.h"

const int MOD = 1000000007;
const int MAXEXP = 200 + 1;

math::FibPowerSum fibPowSum(MOD, MAXEXP);
math::StirlingFirst stirling(MAXEXP, MOD);

inline int calc(int exp, long long n) {
  int res = 0;
  for (int i = 0; i <= exp; ++i) {
    res = math::addMod(
        res,
        math::mulMod(stirling.calcSigned(exp, i), fibPowSum.calc(n, i), MOD),
        MOD);
  }
  res = math::mulMod(res, fibPowSum._comb._invFacs[exp], MOD);
  return res;
}

int main() {
  int exp;
  long long lower, upper;
  scanf("%d%lld%lld", &exp, &lower, &upper);
  printf("%d\n", math::subMod(calc(exp, upper + 2), calc(exp, lower + 1), MOD));
  return 0;
}
