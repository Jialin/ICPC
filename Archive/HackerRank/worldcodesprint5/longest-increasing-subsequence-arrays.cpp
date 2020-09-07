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
#include "math/mod/exp.h"

const int MAXM = 500000 + 1;
const int MOD = 1000000007;

math::CombinationMod combMod(MAXM, MOD);

int powN1[MAXM];
int powN[MAXM];

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, m;
    scanf("%d%d", &m, &n);
    int res = 0;
    powN[0] = powN1[0] = 1;
    for (int i = 1; i <= m - n; ++i) {
      powN[i] = math::mulMod(powN[i - 1], n, MOD);
      powN1[i] = math::mulMod(powN1[i - 1], n - 1, MOD);
    }
    for (int tail = 0; tail <= m - n; ++tail) {
      res = math::addMod(
          res,
          math::mulMod(
              math::mulMod(
                  combMod.calc(m - tail - 1, n - 1), powN1[m - tail - n], MOD),
              powN[tail],
              MOD),
          MOD);
    }
    printf("%d\n", res);
  }
  return 0;
}
