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

#define BIGINT_ADD
#define BIGINT_ASSIGN_INT
#define BIGINT_EQ_INT
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_LT
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "math/bigint/bigint.h"

const int MAXCNT = 500;
const int MAXL = 128;

char as[MAXL], bs[MAXL];
math::BigInt<9, int> fibs[MAXCNT], a, b;

int main() {
  fibs[0] = 1;
  fibs[1] = 2;
  for (int i = 2; i < MAXCNT; ++i) {
    fibs[i] = fibs[i - 2] + fibs[i - 1];
  }
  while (scanf("%s%s", as, bs) != EOF) {
    a.initCharArray(as);
    b.initCharArray(bs);
    if (a == 0 && b == 0) {
      break;
    }
    int idxA = lower_bound(fibs, fibs + MAXCNT, a) - fibs;
    int idxB = upper_bound(fibs, fibs + MAXCNT, b) - fibs;
    printf("%d\n", max(idxB - idxA, 0));
  }
  return 0;
}
