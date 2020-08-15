#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
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

#include "math/prime/phi_all.h"

const int BOUND = 10000 + 1;

math::PhiAll phi(BOUND);
uint64_t ps[BOUND];

int main() {
  for (int n = 1; n < BOUND; ++n) {
    ps[n] = ps[n - 1] + phi.get(n);
  }
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    scanf("%d", &n);
    printf("%llu\n", ps[n] * ps[n]);
  }
  return 0;
}
