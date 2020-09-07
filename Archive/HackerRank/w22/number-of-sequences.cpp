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
#include "math/mod/mul.h"
#include "math/prime/divisor_use_tagger.h"
#include "math/prime/min_prime_tagger.h"

const int MAXN = 100000 + 1;
const int MOD = 1000000007;

math::MinPrimeTagger tagger(MAXN);
int n;
int a[MAXN];

inline int calc() {
  bool valid = true;
  for (int i = 1; i <= n; ++i) {
    if (a[i] < 0) {
      continue;
    }
    math::divisorIteratorUseTagger(
        i, tagger, [&valid, value = a[i]](int factor) {
          if (a[factor] < 0) {
            a[factor] = value % factor;
          } else if (a[factor] != value % factor) {
            valid = false;
            return false;
          }
          return true;
        });
    if (!valid) {
      return 0;
    }
  }
  int res = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i] >= 0) {
      continue;
    }
    int prime, primeCnt, nxtI;
    tagger.process(i, prime, primeCnt, nxtI);
    if (nxtI == 1) {
      res = math::mulMod(res, prime, MOD);
    }
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  printf("%d\n", calc());
  return 0;
}
