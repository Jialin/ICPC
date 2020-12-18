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

#define BIGINT_ADD_INLINE
#define BIGINT_ASSIGN_INT
#define BIGINT_INIT_CAPACITY
#define BIGINT_PRINT

#include "debug/debug.h"
#include "math/bigint.h"

const int MAXL = 2090;

math::BigInt<> zero, one, newZero, newOne;

int main() {
  zero.initCapacity(MAXL);
  one.initCapacity(MAXL);
  newZero.initCapacity(MAXL);
  newOne.initCapacity(MAXL);
  int n;
  scanf("%d", &n);
  zero = 1;
  one = 1;
  for (int i = 1; i < n; ++i) {
    swap(zero, one);
    one += zero;
  }
  one += zero;
  one.print();
  putchar('\n');
}
