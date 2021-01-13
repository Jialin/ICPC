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

#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_MUL_INLINE
#define BIGINT_OUTPUT
#include "math/bigint/bigint_macros.h"

#include "debug/debug.h"
#include "math/bigint/bigint.h"

const int MAXL = 256;

char as[MAXL], bs[MAXL];
math::BigInt<4, int64_t, long double> a, b;

int main() {
  while (scanf("%s%s", as, bs) != EOF) {
    a.initCharArray(as);
    b.initCharArray(bs);
    a *= b;
    a.output();
    putchar('\n');
  }
  return 0;
}
