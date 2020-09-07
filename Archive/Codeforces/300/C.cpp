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

#include "math/mod/add.h"
#include "math/mod/combination.h"

const int MAXN = 1000000 + 1;
const int MOD = 1000000007;

int a, b, n;
math::CombinationMod combMod(MAXN, MOD);

inline bool isExcellent(int sum) {
  for (; sum; sum /= 10) {
    int digit = sum % 10;
    if (digit != a && digit != b) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d%d%d", &a, &b, &n);
  int res = 0;
  int sum = n * b, delta = a - b;
  for (int i = 0; i <= n; ++i) {
    if (isExcellent(sum)) {
      res = math::addMod(res, combMod.calc(n, i), MOD);
    }
    sum += delta;
  }
  printf("%d\n", res);
  return 0;
}
