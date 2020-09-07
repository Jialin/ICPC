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
#include "math/chinese_remainder.h"
#include "math/combination/combination_prime.h"
#include "math/mod/add.h"
#include "math/mod/sub.h"
#include "math/prime/prime_generator.h"

int n, l, r;

math::PrimeGenerator primes(static_cast<int>(sqrt(2000000000) + 100));
math::CombinationModPrime<> comb;

inline void calc(int prime, int cnt, int mod, int& globalRes, int& globalMod) {
  comb.init(n + 1, prime, cnt);
  int res = 0;
  for (int total = 0; total <= n; ++total) {
    res = math::addMod(
        res,
        math::mulMod(
            comb.calc(n, total),
            math::subMod(
                comb.calc(total, (l + total + 1) >> 1),
                comb.calc(total, ((r + total) >> 1) + 1),
                mod),
            mod),
        mod);
  }
  math::chineseRemainder<int, int64_t, uint32_t>(
      globalRes, globalMod, res, mod, globalRes, globalMod);
}

int mod;

int main() {
  scanf("%d%d%d%d", &n, &mod, &l, &r);
  int res = 0, resMod = 1;
  for (int prime : primes.primes) {
    if (prime > mod / prime) {
      break;
    }
    if (mod % prime) {
      continue;
    }
    int prevMod = mod;
    mod /= prime;
    int cnt = 1;
    for (; !(mod % prime); mod /= prime, ++cnt) {}
    calc(prime, cnt, prevMod / mod, res, resMod);
  }
  if (mod > 1) {
    calc(mod, 1, mod, res, resMod);
  }
  printf("%d\n", res);
  return 0;
}
