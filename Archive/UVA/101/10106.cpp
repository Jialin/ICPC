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
#define BIGINT_PRINT

#include "debug/debug.h"
#include "math/bigint.h"

const int MAXL = 256;

char as[MAXL], bs[MAXL];
math::BigInt<9, int64_t> a, b;

int main() {
  while (scanf("%s%s", as, bs) != EOF) {
    a.initCharArray(as);
    b.initCharArray(bs);
    a *= b;
    a.print();
    putchar('\n');
  }
  return 0;
}
