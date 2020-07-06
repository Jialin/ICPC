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

#include "math/prime/factorize64.h"

int main() {
  uint64_t n;
  scanf("%llu", &n);
  int res = 1;
  math::factorize64(n, [&res](uint64_t, int exp) { res *= exp + 1; });
  printf("%d\n", res);
}
