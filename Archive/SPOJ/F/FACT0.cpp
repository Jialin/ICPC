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
  vector<pair<uint64_t, int>> parts;
  const auto& processor = [&parts](uint64_t prime, int exp) {
    parts.emplace_back(prime, exp);
  };
  while (scanf("%llu", &n) != EOF && n) {
    parts.clear();
    math::factorize64(n, processor);
    sort(parts.begin(), parts.end());
    bool first = true;
    for (const auto& part : parts) {
      if (!first) {
        putchar(' ');
      } else {
        first = false;
      }
      printf("%llu^%d", part.first, part.second);
    }
    putchar('\n');
  }
}
