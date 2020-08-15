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

#include "math/mod/power_tower.h"
#include "math/prime/phi32.h"
#include "math/prime/prime_generator.h"

int main() {
  freopen("calc.in", "r", stdin);
  freopen("calc.out", "w", stdout);
  int n, k;
  scanf("%d%d", &n, &k);
  math::PrimeGenerator generator(static_cast<int>(sqrt(k) + 10));
  // printf("size:%lu\n", generator.primes.size());
  vector<int> bases{2, 2, n};
  vector<int> phis;
  phis.reserve(3);
  phis.push_back(k);
  while (phis.size() < 3U && phis.back() != 1) {
    phis.push_back(math::phi32(phis.back(), generator.primes));
  }
  int res = math::powerTower(bases, phis) + 1;
  printf("%d\n", res == k ? 0 : res);
}
