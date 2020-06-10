#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "math/mod/add.h"
#include "math/mod/fib.h"

using namespace std;

inline int calc(const long long& n) {
  if (!n) {
    return 0;
  }
  if (n == 1) {
    return 2;
  }
  int a, b;
  tie(a, b) = math::fib(n + 1);
  return math::addMod(a, b);
}

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    long long n;
    scanf("%lld", &n);
    printf("%d\n", calc(n));
  }
  return 0;
}
