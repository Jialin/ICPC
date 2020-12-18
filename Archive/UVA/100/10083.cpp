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

#define BIGINT_ADD_INT
#define BIGINT_ASSIGN_INT
#define BIGINT_DIGIT_COUNT
#define BIGINT_MUL_INLINE
#define BIGINT_MUL
#define BIGINT_PRINT

#include "debug/debug.h"
#include "math/bigint.h"

int t, a, b;
math::BigInt<> res, bigT, bigTB;

inline bool calc() {
  if (a % b || t == 1) {
    return false;
  }
  res = 1;
  if (a == b) {
    return true;
  }
  bigT = t;
  bigTB = bigT;
  for (int i = b - 1; i > 0; --i) {
    bigTB *= bigT;
    if (bigTB.digitCount() >= 100) {
      return false;
    }
  }
  res = 1;
  for (int i = a / b - 1; i > 0; --i) {
    res = res * bigTB + 1;
    if (res.digitCount() >= 100) {
      return false;
    }
  }
  return true;
}

int main() {
  while (scanf("%d%d%d", &t, &a, &b) != EOF) {
    printf("(%d^%d-1)/(%d^%d-1) ", t, a, t, b);
    if (calc()) {
      res.print();
      putchar('\n');
    } else {
      puts("is not an integer with less than 100 digits.");
    }
  }
  return 0;
}
