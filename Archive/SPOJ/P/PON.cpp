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

#include "math/prime/miller_rabin.h"

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    uint64_t n;
    scanf("%llu", &n);
    puts(math::millerRabin(n) ? "YES" : "NO");
  }
  return 0;
}
