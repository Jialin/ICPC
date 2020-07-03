#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "math/prime/prime_iterator.h"

using namespace std;

const int MAXN = 100000;

math::PrimeIterator pg(MAXN);
vector<long long> pp;

int main() {
  pp.reserve(9592);
  pg.iterate(MAXN, [](int p) { pp.push_back(static_cast<long long>(p) * p); });
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    long long n, k;
    scanf("%lld%lld", &n, &k);
    int pnt2 =
        static_cast<int>(upper_bound(pp.begin(), pp.end(), n) - pp.begin() - 1);
    int pnt1 =
        static_cast<int>(lower_bound(pp.begin(), pp.end(), k + 1) - pp.begin());
    printf("%d %d\n", pnt2 + 1, max(pnt2 - pnt1 + 1, 0));
  }
  return 0;
}
