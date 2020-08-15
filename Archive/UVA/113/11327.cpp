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

#include "math/prime/factorize.h"
#include "math/prime/phi_all.h"

const int BOUND = 200000 + 1;

math::PhiAll phi(BOUND);
math::MinPrimeTagger tagger(BOUND);
long long phiSum[BOUND];

vector<int> primes;
vector<pair<int, bool>> ies;
auto factorizeProcessor = [](int prime, int) {
  primes.push_back(prime);
  return true;
};

inline void dfs(int primeIdx, int product, bool positive) {
  if (primeIdx < 0) {
    ies.emplace_back(product, positive);
    return;
  }
  dfs(primeIdx - 1, product, positive);
  dfs(primeIdx - 1, product * primes[primeIdx], !positive);
}

inline int calc(int den, int idx) {
  if (den == 1) {
    return idx;
  }
  if (idx == 1) {
    return 1;
  }
  primes.clear();
  math::factorize(den, tagger, factorizeProcessor);
  ies.clear();
  dfs(static_cast<int>(primes.size()) - 1, 1, true);
  sort(ies.begin(), ies.end());
  int res = den - 1;
  for (int lower = 2, upper = res; lower < upper;) {
    int medium = (lower + upper) >> 1;
    int sum = 0;
    for (const auto& ie : ies) {
      if (ie.first > medium) {
        break;
      }
      if (ie.second) {
        sum += medium / ie.first;
      } else {
        sum -= medium / ie.first;
      }
    }
    if (sum >= idx) {
      res = medium;
      upper = medium;
    } else {
      lower = medium + 1;
    }
  }
  return res;
}

const int MAX_PFCNT = 6;

int main() {
  primes.reserve(MAX_PFCNT);
  ies.reserve(1 << MAX_PFCNT);
  phiSum[0] = 1;
  for (int i = 1; i < BOUND; ++i) {
    phiSum[i] = phiSum[i - 1] + phi.get(i);
  }
  long long n;
  while (true) {
    scanf("%lld", &n);
    if (!n) {
      break;
    }
    int den =
        static_cast<int>(lower_bound(phiSum + 1, phiSum + BOUND, n) - phiSum);
    printf("%d/%d\n", calc(den, static_cast<int>(n - phiSum[den - 1])), den);
  }
}
