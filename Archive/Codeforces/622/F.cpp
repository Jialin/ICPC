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
#include "math/mod/add.h"
#include "math/mod/exp.h"
#include "math/mod/inv.h"
#include "math/mod/inv_all.h"
#include "math/mod/mul.h"
#include "math/mod/sub.h"
#include "math/prime/min_prime_tagger.h"

const int MOD = 1000000007;
const int MAXN = 1000000 + 3;
const int INV_N1 = math::invMod(MOD - 1, MOD);

math::InvModAll invModAll(MAXN, MOD);
math::MinPrimeTagger tagger(MAXN);

int mul[MAXN], powK[MAXN], invFacs[MAXN];

inline int calc(int n, int k) {
  powK[1] = 1;
  for (int i = 2; i <= k + 2; ++i) {
    int prime, primeCnt, nxtN;
    tagger.process(i, prime, primeCnt, nxtN);
    if (i == prime) {
      powK[i] = math::expMod(i, k, MOD);
    } else {
      powK[i] = math::mulMod(powK[prime], powK[i / prime], MOD);
    }
  }
  if (n <= k + 2) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
      res = math::addMod(res, powK[i], MOD);
    }
    return res;
  }
  invFacs[0] = 1;
  int forwardP = 1;
  for (int i = 1; i <= k + 2; ++i) {
    mul[i - 1] = forwardP;
    forwardP = math::mulMod(forwardP, n - i, MOD);
    invFacs[i] = math::mulMod(invFacs[i - 1], invModAll.get(i), MOD);
  }
  int backwardP = 1;
  for (int i = k + 2; i >= 1; --i) {
    mul[i - 1] = math::mulMod(mul[i - 1], backwardP, MOD);
    backwardP = math::mulMod(backwardP, n - i, MOD);
  }
  int v = 0, res = 0;
  for (int i = 1; i <= k + 2; ++i) {
    v = math::addMod(v, powK[i], MOD);
    int subRes = math::mulMod(
        v,
        math::mulMod(
            mul[i - 1],
            math::mulMod(invFacs[i - 1], invFacs[k + 2 - i], MOD),
            MOD),
        MOD);
    if ((k + 2 - i) & 1) {
      res = math::subMod(res, subRes, MOD);
    } else {
      res = math::addMod(res, subRes, MOD);
    }
  }
  return res;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  printf("%d\n", calc(n, k));
  return 0;
}
