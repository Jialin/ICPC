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

#define BIGINT_DIV_INLINE
#define BIGINT_GCD_INLINE
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_OUTPUT
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "math/bigint/bigint.h"

const int MAXL = 32;

char ps[MAXL], qs[MAXL];
math::BigInt<> p, q;
math::BigInt<> a, b;

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    scanf("%s / %s", ps, qs);
    p.initCharArray(ps);
    q.initCharArray(qs);
    a = p;
    b = q;
    a.gcdInline(b);
    p /= a;
    q /= a;
    p.output();
    putchar(' ');
    putchar('/');
    putchar(' ');
    q.output();
    putchar('\n');
  }
  return 0;
}
