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

#include "math/prime/min_prime_tagger.h"

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  math::MinPrimeTagger tagger(n);
  int res = 0;
  for (int i = 6; i <= n; ++i) {
    int rem = i, cnt = 0;
    if (!(rem & 1)) {
      rem >>= __builtin_ctz(rem);
      cnt = 1;
    }
    for (; rem > 1 && cnt < 3; ++cnt) {
      int p = tagger.getMinPrimeFactor(rem);
      for (rem /= p; !(rem % p); rem /= p) {}
    }
    res += cnt == 2;
  }
  printf("%d\n", res);
}
