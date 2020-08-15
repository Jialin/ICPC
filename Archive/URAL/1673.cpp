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

#include "math/prime/phi_inv64.h"

math::PhiInv64 phiInv;

int main() {
  int n;
  scanf("%d", &n);
  uint64_t res = 0;
  phiInv.calc(n, [&res](uint64_t v) {
    if (!res) {
      res = v;
    } else {
      res = min(res, v);
    }
  });
  printf("%llu\n", res);
}
