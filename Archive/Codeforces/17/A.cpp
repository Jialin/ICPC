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

#include "math/prime/prime_iterator.h"

const int MAXN = 1000 + 1;

math::PrimeIterator pi(MAXN);
int cnt[MAXN];
bool isPrime[MAXN];

int main() {
  int lastP = -1;
  pi.iterate(MAXN, [&lastP](int prime) {
    isPrime[prime] = true;
    if (lastP > 0 && lastP + prime + 1 < MAXN) {
      cnt[lastP + prime + 1] = 1;
    }
    lastP = prime;
  });
  for (int i = 2; i < MAXN; ++i) {
    if (!isPrime[i]) {
      cnt[i] = 0;
    }
    cnt[i] += cnt[i - 1];
  }
  int n, k;
  scanf("%d%d", &n, &k);
  puts(cnt[n] >= k ? "YES" : "NO");
  return 0;
}
